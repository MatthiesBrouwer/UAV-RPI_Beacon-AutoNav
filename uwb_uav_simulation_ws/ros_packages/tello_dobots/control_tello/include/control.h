/*
 * Author: bart 
 * Date: 02/12/2019
 *
 */

// This is for the compiler to check if this header file is already included, if not it is included.
#ifndef CONTROL_H
#define CONTROL_H

// include all necessary files, functions, and messages
#include <ros/ros.h>
#include <control_tello_msgs/StartAction.h>
#include <control_tello_msgs/MoveDroneAction.h> 
#include <actionlib/client/simple_action_client.h>

// The class definition is inside the talker namespace. 
namespace manual_control{
	// Class definition
	class Control{
		ros::NodeHandle nh_; // make sure this is initialized first
		// action clients
		actionlib::SimpleActionClient<control_tello_msgs::MoveDroneAction> ac;
		actionlib::SimpleActionClient<control_tello_msgs::StartAction> acs;

		// timer for main control loop 
		ros::Timer timer_t;
		// helper variables	
		bool land_;		// allow goal to be send to land server
		bool takeoff_;
		bool approach_;
		bool temp_bool_;
		// goal attributes
		control_tello_msgs::MoveDroneGoal goal_;
		control_tello_msgs::StartGoal goal_takeoff_;
		control_tello_msgs::StartGoal goal_land_;
	public:		
		// constructor definition
		Control(std::string name_server); 			
		// subscribers & publishers
    	ros::Subscriber state_sub_; // get current state
		// callback function for action client 
		void doneCb(const actionlib::SimpleClientGoalState& state, const control_tello_msgs::MoveDroneResultConstPtr& result);	
		//void activeCb();
        //void feedbackCb(const control_tello_msgs::MoveDroneFeedbackConstPtr& feedback);
		void doneLandingCb(const actionlib::SimpleClientGoalState& state, const control_tello_msgs::StartResultConstPtr& result);
		// callback functions
		void periodicControl(const ros::TimerEvent& event);
		void checkRosParam();
	}; // end class
} // end namespace

#endif // MANUAL_H
