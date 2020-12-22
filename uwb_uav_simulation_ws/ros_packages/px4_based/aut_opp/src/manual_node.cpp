/*
 * Author: bart
 * Date: 21/10/2019
 */

#include <ros/ros.h>
#include <manual.h>

int main(int argc, char **argv){
  	// Initialize ros
  	ros::init(argc, argv, "control_node");
	// make object to track drone state
	manual_control::Control drone_state("move_drone");	
	ros::spin();
}
