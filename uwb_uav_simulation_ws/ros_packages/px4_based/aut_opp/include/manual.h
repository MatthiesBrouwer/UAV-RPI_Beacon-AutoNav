/*
 * Author: bart 
 * Date: 21/10/2019
 *
 */

// This is for the compiler to check if this header file is already included, if not it is included.
#ifndef MANUAL_H
#define MANUAL_H

// include all necessary files, functions, and messages
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/State.h>
#include <aut_opp_msgs/StartAction.h>
#include <aut_opp_msgs/MoveDroneAction.h> 
#include <actionlib/client/simple_action_client.h>

// The class definition is inside the talker namespace. 

namespace manual_control{

	// Class definition
	class Control{

		ros::NodeHandle nh_; // make sure this is initialized first
		// action clients
		actionlib::SimpleActionClient<aut_opp_msgs::MoveDroneAction> ac;
		actionlib::SimpleActionClient<aut_opp_msgs::StartAction> acs;
		actionlib::SimpleActionClient<aut_opp_msgs::StartAction> acl;		
			
		// subscribers
    	ros::Subscriber state_sub_; // get current state
    	ros::Subscriber pos_sub_; // get current pos
		ros::Publisher pos_pub_; // publish setpoint	
    	ros::Subscriber target_sub_; // get current target

		// timer for main control loop 
		ros::Timer timer_t;

	public:		
		// helper variables	
		bool mode_has_been_set_;
		bool go_land_;		// allow goal to be send to land server
		bool start_counting_; // helper variable 
		bool once_; // needs to eb replaced by manual command
		double tol_; 	// tolerance around target position
		double dist_; // distance between position and target. 
		ros::Time begin_time_; // start time when position reached
		ros::Duration wait_time_; // wait time
		bool temp_string_;

		// goal attributes
		aut_opp_msgs::MoveDroneGoal goal_;
		aut_opp_msgs::StartGoal goal_mode_;
		aut_opp_msgs::StartGoal goal_land_;
		// messages 
		mavros_msgs::State current_state_; // check if connection is there
		geometry_msgs::PoseStamped current_pos_; //save current goal		
		geometry_msgs::PoseStamped current_target_; //save current goal	
		
		
		// constructor definition
		Control(std::string name_server); 		

		// callback function for action client 
		void doneCb(const actionlib::SimpleClientGoalState& state, const aut_opp_msgs::MoveDroneResultConstPtr& result);	
		void doneLandingCb(const actionlib::SimpleClientGoalState& state, const aut_opp_msgs::StartResultConstPtr& result);
		// callback functions
		void periodicControl(const ros::TimerEvent& event);
		void state(const mavros_msgs::State::ConstPtr& msg);
		void currPos(const geometry_msgs::PoseStamped::ConstPtr& msg);
		void target(const geometry_msgs::PoseStamped::ConstPtr& msg);
		void pubPos();
		void checkRosParam();
	}; // end class
} // end namespace

#endif // MANUAL_H
