cmake_minimum_required(VERSION 2.8.3)
project(control_tello_msgs)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
		actionlib_msgs
		message_generation
		std_msgs
		roscpp
		roslib
		)

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate actions in the 'action' folder
 add_action_files(
   		DIRECTORY action
		FILES MoveDrone.action Start.action
   		)

## Generate code for messages we define
add_message_files(
		DIRECTORY msg 
		FILES FlightData.msg Flip.msg
		)

## Generate added messages and services with any dependencies listed here
 generate_messages(
  		DEPENDENCIES std_msgs actionlib_msgs  
  		)

###################################
## catkin specific configuration ##
###################################
 catkin_package(
		CATKIN_DEPENDS message_runtime actionlib_msgs 	
		)

###########
## Build ##
###########

include_directories(
 		include ${catkin_INCLUDE_DIRS}
		)	

