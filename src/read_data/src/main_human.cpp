#include <ros/ros.h>
#include <geometry_msgs/WrenchStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

std::ofstream wrench_file, wrench2_file, vision_file;

void wrenchCallback(const geometry_msgs::WrenchStamped::ConstPtr& msg)
{
    wrench_file << msg->header.stamp << ", "
                << msg->wrench.force.x << ", " << msg->wrench.force.y << ", " << msg->wrench.force.z << ", "
                << msg->wrench.torque.x << ", " << msg->wrench.torque.y << ", " << msg->wrench.torque.z << std::endl;
}

void wrench2Callback(const geometry_msgs::WrenchStamped::ConstPtr& msg)
{
    wrench2_file << msg->header.stamp << ", "
                << msg->wrench.force.x << ", " << msg->wrench.force.y << ", " << msg->wrench.force.z << ", "
                << msg->wrench.torque.x << ", " << msg->wrench.torque.y << ", " << msg->wrench.torque.z << std::endl;
}

// void imuCallback(const sensor_msgs::Imu::ConstPtr& msg)
// {
//     imu_file  << msg->angular_velocity.x << ", " << msg->angular_velocity.y << ", " << msg->angular_velocity.z << ", "
//               << msg->linear_acceleration.x << ", " << msg->linear_acceleration.y << ", " << msg->linear_acceleration.z << std::endl;
// }

void visionCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    vision_file << msg->header.stamp << ", "
                << msg->pose.position.x << ", " << msg->pose.position.y << ", " << msg->pose.position.z << ", "
                << msg->pose.orientation.x << ", " << msg->pose.orientation.y << ", " << msg->pose.orientation.z << ", " << msg->pose.orientation.w << std::endl;
}

char getch()
{
    char buf = 0;
    struct termios old;
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

// ... [중략: 기존에 있던 코드들은 유지]

int main(int argc, char** argv)
{
    ros::init(argc, argv, "subscriber_node");
    ros::NodeHandle nh;
    ros::Rate loop_rate(500);  // 500Hz loop rate

    std::cout << "Press 's' to start subscribing and logging. Press 'q' to quit." << std::endl;
    char input;
    std::cin >> input;

    if (input != 's')
    {
        return 0;
    }

    wrench_file.open("wrench_data.txt", std::ofstream::out);
    wrench2_file.open("wrench2_data.txt", std::ofstream::out);
    vision_file.open("vision_data.txt", std::ofstream::out);

    ros::Subscriber wrench_sub = nh.subscribe("/ft_1/RFT_FORCE", 5000, wrenchCallback);
    ros::Subscriber wrench2_sub = nh.subscribe("/ft_2/RFT_FORCE_2", 5000, wrench2Callback);
    ros::Subscriber vision_sub = nh.subscribe("aruco_single/pose", 5000, visionCallback);

    std::cout << "Subscribing... Press 'q' to quit." << std::endl;

    fd_set set;
    struct timeval timeout;

    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);

    timeout.tv_sec = 0;
    timeout.tv_usec = 100;  // Set timeout for non-blocking read

    while (ros::ok())
    {
        ros::spinOnce();
        // loop_rate.sleep();  // Sleep to maintain the loop rate

        int res = select(STDIN_FILENO+1, &set, NULL, NULL, &timeout);

        if (res > 0)
        {
            char c = getch();
            if (c == 'q')
            {
                break;
            }
        }
    }

    wrench_file.close();
    wrench2_file.close();
    vision_file.close();

    return 0;
}

