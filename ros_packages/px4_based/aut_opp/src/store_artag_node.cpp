/*
 * Author: bart
 * Date: 6/11/2019
 *
 */

// All declarations of variables and functions are described in the header.
#include <store_artag.h>

int main(int argc, char **argv){
  	// Initialize ros
  	ros::init(argc, argv, "store_artag_node");

	// make object.
  	store::Store tags("store_artag");
	
	//let ros take over
  	ros::spin();
}
