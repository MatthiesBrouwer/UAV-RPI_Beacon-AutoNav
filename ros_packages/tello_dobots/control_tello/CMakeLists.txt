cmake_minimum_required(VERSION 2.8.3)
project(control_tello)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
		geometry_msgs
		control_tello_msgs
		actionlib_msgs
		roscpp
		roslib
		tf
		cv_bridge
  		control_tello_msgs
  		rospy
  		sensor_msgs
  		std_msgs
		)

###################################
## catkin specific configuration ##
###################################
 catkin_package( CATKIN_DEPENDS 
		actionlib_msgs 
		control_tello_msgs 
		geometry_msgs 
		cv_bridge
  		flock_msgs
  		rospy
  		sensor_msgs
  		std_msgs
	)

###########
## Build ##
###########


include_directories(
 	include
 	${catkin_INCLUDE_DIRS}
)

## Declare a C++ library

add_library(control_tello 
		src/control.cpp
		src/takeoff_land.cpp
		src/move_drone.cpp
		)

target_link_libraries( control_tello ${catkin_LIBRARIES})

## Declare a C++ executable

add_executable(control_node src/control_node.cpp)
add_dependencies(control_node  ${catkin_EXPORTED_TARGETS})
target_link_libraries(control_node control_tello ${catkin_LIBRARIES})
set_target_properties(control_node PROPERTIES OUTPUT_NAME "control")

add_executable(takeoff_land_node src/takeoff_land_node.cpp)
add_dependencies(takeoff_land_node  ${catkin_EXPORTED_TARGETS})
target_link_libraries(takeoff_land_node control_tello ${catkin_LIBRARIES})
set_target_properties(takeoff_land_node PROPERTIES OUTPUT_NAME "takeoff_land")

add_executable(move_drone_node src/move_drone_node.cpp)
add_dependencies(move_drone_node  ${catkin_EXPORTED_TARGETS})
target_link_libraries(move_drone_node control_tello ${catkin_LIBRARIES})
set_target_properties(move_drone_node PROPERTIES OUTPUT_NAME "move_drone")
################
## Install #####
################


