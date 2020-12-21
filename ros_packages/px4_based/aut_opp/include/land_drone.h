/*
 * Author: bart 
 * Date: 25/10/2019
 *
This is the header file of the move_drone class lib.
 */

#ifndef LAND_DRONE_H
#define LAND_DRONE_H

// include all necessary files, functions, and messages
#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <geometry_msgs/PoseStamped.h>
#include <aut_opp_msgs/StartAction.h> // goal message header file
#include <mavros_msgs/CommandTOL.h> 
#include <mavros_msgs/CommandBool.h>

// The class definition is inside the talker namespace. Namespaces are used. e collisions.
namespace land_drone{
	// Class definition
	class Land{
	  	public:
    // constructor definition
	    Land(std::string name);
	// member functions
		void land(const aut_opp_msgs::StartGoalConstPtr &goal);
		void currPos(const geometry_msgs::PoseStamped::ConstPtr& msg);
	// subscriber
		ros::Subscriber pos_sub_; // get current pos

		private:
		ros::NodeHandle nh_; // ros node handle
	// action server handle
		actionlib::SimpleActionServer<aut_opp_msgs::StartAction> as_;
	// action server needed attributes
		std::string action_name_;
	// servers connection needed
		ros::ServiceClient land_; 
		// mavros_msgs::CommandBool arm_cmd_;  // set local to true for arming
		mavros_msgs::CommandTOL land_set_mode_; //local msg

	// class vars
		aut_opp_msgs::StartFeedback feedback_; 
		aut_opp_msgs::StartResult result_;	
		bool stop_;
		bool pos_received_;

	}; // end class
} // end namespace

#endif // LAND_DRONE_H

