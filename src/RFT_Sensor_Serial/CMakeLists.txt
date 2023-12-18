cmake_minimum_required(VERSION 2.8.3)
project(rft_sensor_serial)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  message_generation
  std_msgs
  roscpp
)


################################################
## Declare ROS messages, services and actions ##
################################################

## Generate services in the 'srv' folder
add_service_files( FILES rft_operation.srv  rft_operation_2.srv)
generate_messages(DEPENDENCIES std_msgs)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES rft_sensor_serial
  CATKIN_DEPENDS geometry_msgs std_msgs roscpp
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

## Declare a cpp executable
add_executable(${PROJECT_NAME}
	src/main_1.cpp
	src/RFT_COM.cpp
	src/RFT_IF_PACKET_Rev1.2.cpp
)

add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

add_executable(rft_sensor_serial_2
	src/main_2.cpp
	src/RFT_COM.cpp
	src/RFT_IF_PACKET_Rev1.2.cpp
)

add_dependencies(rft_sensor_serial_2 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(rft_sensor_serial_2 ${catkin_LIBRARIES})


