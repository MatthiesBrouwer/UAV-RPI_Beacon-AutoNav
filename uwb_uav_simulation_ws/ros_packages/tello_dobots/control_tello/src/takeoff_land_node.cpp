/*
 * Author: bart
 * Date: 02/12/2019
 */

// All declarations of variables and functions are described in the header.

#include <takeoff_land.h>

int main(int argc, char **argv){
  	// Initialize ros
  	ros::init(argc, argv, "takeoff_land");
	ROS_INFO("ros initiated");
	// object made.
  	takeoff_land::TakeOffLand go("takeoff_land");
	ROS_INFO("takeoff and land object made");	
	ros::spin();
	//return 0;
}
