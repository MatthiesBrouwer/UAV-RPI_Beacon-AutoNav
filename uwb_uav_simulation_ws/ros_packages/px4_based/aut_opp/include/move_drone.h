/*
 * Author: bart 
 * Date: 26/09/2019
 *
This is the header file of the move_drone class lib.
 */

#ifndef MOVE_DRONE_H
#define MOVE_DRONE_H

// include all necessary files, functions, and messages
#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <geometry_msgs/PoseStamped.h>
#include <aut_opp_msgs/MoveDroneAction.h> // goal message header file
#include <tf/transform_listener.h> //transformer class

// The class definition is inside the talker namespace. Namespaces are used. e collisions.
namespace move_drone{

	// Class definition
	class MoveDrone{
	  	public:
    // constructor definition
	    MoveDrone(std::string name);
		//~Follow();
	// member functions
		void follow(const aut_opp_msgs::MoveDroneGoalConstPtr &goal);

		private:
		// ros node handle
		ros::NodeHandle nh_; 
		// action server handle
		actionlib::SimpleActionServer<aut_opp_msgs::MoveDroneAction> as_;
		// action server needed attributes
		std::string action_name_;
		// class vars
		aut_opp_msgs::MoveDroneFeedback feedback_; // double check this//////////////////////
		aut_opp_msgs::MoveDroneResult result_;	///////////// double checkkkk ///////////
		ros::Publisher pub_; // publisher of new setpoint			
		geometry_msgs::PoseStamped setpoint_; // published new setpoint
		bool stop_;
		bool reduce_height;
		bool increase_height;
		float Xd_;
		float Yd_;
		float tol_;
		//tf transform objects
		tf::TransformListener listener_; //does the lookuptransform
		tf::StampedTransform transform_;		

	}; // end class
} // end namespace

#endif // MOVE_DRONE_H

