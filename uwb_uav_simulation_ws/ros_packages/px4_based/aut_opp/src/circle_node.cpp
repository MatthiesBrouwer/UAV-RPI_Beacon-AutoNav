/*
 * Author: bart
 * Date: 6/11/2019
 *
 *	initiate the circle path object.
 *
 */

#include <circle.h>

int main(int argc, char **argv){
  	// Initialize ros
  	ros::init(argc, argv, "circle_node");

	// make rectangle object.
  	circle::Circle path("circle");
  	ros::spin();
}
