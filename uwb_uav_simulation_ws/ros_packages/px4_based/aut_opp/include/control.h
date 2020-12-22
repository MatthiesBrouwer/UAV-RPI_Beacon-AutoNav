/*
 * Author: bart 
 * Date: 21/10/2019
 *
 */

// This is for the compiler to check if this header file is already included, if not it is included.
#ifndef CONTROL_H
#define CONTROL_H

// include all necessary files, functions, and messages
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/State.h>
#include <aut_opp_msgs/StartAction.h>
#include <aut_opp_msgs/MoveDroneAction.h> 
#include <actionlib/client/simple_action_client.h>

// The class definition is inside the talker namespace. 

namespace control_drone{

	// Class definition
	class Control{
	  	public:
    	Control(); // constructor definition
		
		// callback functions
		void state(const mavros_msgs::State::ConstPtr& msg);
		void currPos(const geometry_msgs::PoseStamped::ConstPtr& msg);
		void target(const geometry_msgs::PoseStamped::ConstPtr& msg);
		void pubPos();
		
		// callback function for 
		void doneCb(const actionlib::SimpleClientGoalState& state, const aut_opp_msgs::MoveDroneResultConstPtr& result);
		void activeCb();
		void feedbackCb(const aut_opp_msgs::MoveDroneFeedbackConstPtr& feedback);
		
		// local attributes
		mavros_msgs::State current_state_; // check if connection is there
		geometry_msgs::PoseStamped current_pos_; //save current goal		
		geometry_msgs::PoseStamped current_target_; //save current goal	
		bool go_land_;		// allow goal to be send to land server
		
		bool start_counting_; // helper variable 
		private:	

		double tol_; 	// tolerance around target position
		double dist_; // distance between position and target. 
		ros::Time begin_time_; // start time when position reached
		ros::Duration wait_time_; // wait time
		ros::NodeHandle nh_; 
    	ros::Subscriber state_sub_; // get current state
    	ros::Subscriber pos_sub_; // get current pos
		ros::Publisher pos_pub_; // publish setpoint	
    	ros::Subscriber target_sub_; // get current target
	}; // end class
} // end namespace

#endif // CONTROL_H
