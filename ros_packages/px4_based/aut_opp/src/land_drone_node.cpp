/*
 * Author: bart
 * Date: 03/09/2019
 *
 */

// All declarations of variables and functions are described in the header.
#include <land_drone.h>

int main(int argc, char **argv){
  	// Initialize ros
  	ros::init(argc, argv, "land_drone_node");

	// make rectangle object.
  	land_drone::Land land("land_drone");
	ROS_INFO("land object made wait for client");
	//let ros take over
  	ros::spin();
	return 0;
}
