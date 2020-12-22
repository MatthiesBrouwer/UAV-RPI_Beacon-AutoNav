/*
 * Author: bart
 * Date: 26/09/2019
 *
 */

// All declarations of variables and functions are described in the header.
#include <move_drone.h>

int main(int argc, char **argv){
  	// Initialize ros
  	ros::init(argc, argv, "move_drone_node");

	// make rectangle object.
  	move_drone::MoveDrone track("move_drone");
	
	//let ros take over
  	ros::spin();
	return 0;
}
