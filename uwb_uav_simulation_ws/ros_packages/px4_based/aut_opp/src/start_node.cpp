/*
 * Author: bart
 * Date: 23/09/2019
 */

// All declarations of variables and functions are described in the header.

#include <start.h>

int main(int argc, char **argv){
  	// Initialize ros
  	ros::init(argc, argv, "start_node");
	ROS_INFO("ros initiated");
	// object made.
  	start::Start go("start_node");
	ROS_INFO("go object made");	
	//ros::Rate loop_rate(25);
	//while(ros::ok()){
	//ros::spinOnce();
	//loop_rate.sleep();
	//}
	ros::spin();
	//return 0;
}
