/*
 * Author: bart 
 * Date: 25/09/2019
 *
This is the header file of the start_search node.
 */

// This is for the compiler to check if this header file is already included, if not it is included.
#ifndef START_H
#define START_H

// include all necessary files, functions, and messages
#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <aut_opp_msgs/StartAction.h> // action message header file
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/CommandTOL.h>
// The class definition is inside the talker namespace. Namespaces are used. e collisions.
namespace start{

	// Class definition
	class Start {
	  	public:
    // constructor definition
		Start(std::string name);

	// member functions
		void state_(const mavros_msgs::State::ConstPtr& msg);
		void setMode(const aut_opp_msgs::StartGoalConstPtr &goal);
		void currPos(const geometry_msgs::PoseStamped::ConstPtr& msg);
	// attributes	
		mavros_msgs::State current_state_;// check if connection is there
		
		private:
	// action sevrer attributes 
		ros::NodeHandle nh_; 
		actionlib::SimpleActionServer<aut_opp_msgs::StartAction> as_st_;
        aut_opp_msgs::StartResult result_;
        aut_opp_msgs::StartFeedback feedback_;
        std::string action_name_;

	// attributes, according to styling conventions, have a traling underscore.

    	ros::Subscriber state_sub_; // get current state
    	ros::Subscriber pos_sub_; // get current pos
		ros::Publisher pub_; // publisher of new setpoint	
		ros::ServiceClient arming_client_; // service for arming
		ros::ServiceClient set_mode_client_; // service for changing mode
		geometry_msgs::PoseStamped takeoff_point_; // to be published new setpoint
		mavros_msgs::SetMode offb_set_mode_; //local msg
		mavros_msgs::CommandBool arm_cmd_; // local msg
		ros::Time last_request_;
	}; // end class
} // end namespace

#endif 
