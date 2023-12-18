#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <mutex>


#include "ros/ros.h"
#include "rft_sensor_serial/rft_operation_2.h"


int main(int argc, char **argv)
{
  ros::init(argc, argv, "rft_operation_client_2");


  ros::NodeHandle n2;
  ros::ServiceClient client_2 = n2.serviceClient<rft_sensor_serial::rft_operation_2>("rft_serial_op_service_2");
  rft_sensor_serial::rft_operation_2 srv_2;
  
  bool isGo = true;
  bool knownCommand = false;

  while( isGo )
	{
		char cmd = getchar();
		
		if( cmd == 0x1B ) // esc
			isGo = false;
    else if( cmd == 'O' || cmd == 'o' ) // measure Once
		{	
      srv_2.request.opType = 10;
      srv_2.request.param1 = 1;
      srv_2.request.param2 = 0;
      srv_2.request.param3 = 0;
      knownCommand = true;
    }
		else if( cmd == 'M' || cmd == 'm' ) // measure
		{	
      srv_2.request.opType = 11;
      srv_2.request.param1 = 1;
      srv_2.request.param2 = 0;
      srv_2.request.param3 = 0;
      knownCommand = true;
    }
		else if( cmd == 'S' || cmd == 's' ) // stop
		{	
      srv_2.request.opType = 12;
      srv_2.request.param1 = 1;
      srv_2.request.param2 = 0;
      srv_2.request.param3 = 0;
      knownCommand = true;
    }
		else if( cmd == 'B' || cmd == 'b' ) // Set bias
		{	
      srv_2.request.opType = 17;
      srv_2.request.param1 = 1;
      srv_2.request.param2 = 0;
      srv_2.request.param3 = 0;
      knownCommand = true;
    }
 		else if( cmd == 'U' || cmd == 'u' ) // Set Un-bias
		{	 
      srv_2.request.opType = 17;
      srv_2.request.param1 = 0;
      srv_2.request.param2 = 0;
      srv_2.request.param3 = 0; 
      knownCommand = true;
    }  
    else if( cmd == 'D' || cmd == 'd' ) // Set baud-rate 230
		{	
      srv_2.request.opType = 6;
      srv_2.request.param1 = 3;
      srv_2.request.param2 = 0;
      srv_2.request.param3 = 0;
      knownCommand = true;
    } 
    else if( cmd == 'R' || cmd == 'r' ) // OutRate
		{	
      srv_2.request.opType = 15;
      srv_2.request.param1 = 7;
      srv_2.request.param2 = 0;
      srv_2.request.param3 = 0;
      knownCommand = true;
    } 
    else if( cmd == 'T' || cmd == 't' ) // Read OutRate
		{	
      srv_2.request.opType = 16;
      srv_2.request.param1 = 6;
      srv_2.request.param2 = 0;
      srv_2.request.param3 = 0;
      knownCommand = true;
    }
		else if( cmd == 'F' || cmd == 'f' ) // Read baud rate
		{	
      srv_2.request.opType = 7;
      srv_2.request.param1 = 1;
      srv_2.request.param2 = 0;
      srv_2.request.param3 = 0;
      knownCommand = true;
    }
		else if( cmd == 'G' || cmd == 'g' ) // Baud rate 115
		{	
      srv_2.request.opType = 6;
      srv_2.request.param1 = 4;
      srv_2.request.param2 = 0;
      srv_2.request.param3 = 0;
      knownCommand = true;     
    }
		else
		{
			if( cmd != '\r' && cmd != '\n' )
				printf("UNKNOWN COMMAND\n");
		}


    if(knownCommand)
    {

      if (client_2.call(srv_2))
      {
        ROS_INFO("Service2 call succeeded, result: %d", srv_2.response.result);
      }
      else
      {
        ROS_ERROR("Failed to call service2 rft_serial_op_service2");
        return 1;
      }
    }

	}




  return 0;

  
}