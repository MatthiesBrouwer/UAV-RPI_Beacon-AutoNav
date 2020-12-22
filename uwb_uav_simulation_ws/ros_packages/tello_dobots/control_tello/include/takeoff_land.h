/*
 * Author: bart 
 * Date: 25/09/2019
 *
This is the header file of the start_search node.
 */

// This is for the compiler to check if this header file is already included, if not it is included.
#ifndef TAKEOFF_LAND_H
#define TAKEOFF_LAND_H

// include all necessary files, functions, and messages
#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <control_tello_msgs/StartAction.h> // action message header file
#include <std_msgs/Empty.h>
// The class definition is inside the talker namespace. Namespaces are used. e collisions.
namespace takeoff_land{

	// Class definition
	class TakeOffLand{
	  	public:
    // constructor definition
		TakeOffLand(std::string name);
	// member functions
		void setMode(const control_tello_msgs::StartGoalConstPtr &goal);
		
		private:
	// action server attributes 
		ros::NodeHandle nh_; 
		actionlib::SimpleActionServer<control_tello_msgs::StartAction> as_st_;
        control_tello_msgs::StartResult result_;
        control_tello_msgs::StartFeedback feedback_;
        std::string action_name_;

	// attributes, according to styling conventions, have a traling underscore.
		ros::Publisher pub_land_; // publisher of new setpoint		
		ros::Publisher pub_takeoff_; // publisher of new setpoint	
		std_msgs::Empty empty_msg_; // to be published new setpoint
	}; // end class
} // end namespace

#endif 
