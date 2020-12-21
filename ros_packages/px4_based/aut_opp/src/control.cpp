/*
 * Author: bart 
 * Date: 21/10/2019
 */

// All declarations of variables and functions are described in the header.
#include <control.h>

// The class definition is inside its namespace.
namespace control_drone{
	// Constructs instance of the class
	Control::Control(int a){
		// subscribers
		pos_sub_ = nh_.subscribe("/mavros/local_position/pose", 10, &Control::currPos, this);	
		target_sub_ = nh_.subscribe("mavros/setpoint_position/local", 10, &Control::target, this);	
		state_sub_ = nh_.subscribe<mavros_msgs::State>("mavros/state", 10, &Control::state, this);	
		pos_pub_ = nh_.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);
		tol_ = 0.2;
		go_land_ = false;
		start_counting_ = false;
	}
	// State callback function
	void Control::state(const mavros_msgs::State::ConstPtr& msg){
    	current_state_ = *msg;
	}

	// Target callback function
	void Control::target(const geometry_msgs::PoseStamped::ConstPtr& msg){
    	current_target_ = *msg;
	}

	// Position callback function
    void Control::currPos(const geometry_msgs::PoseStamped::ConstPtr& msg){
        //current_pos_ = *msg;
		// Calculate distance to next target point
 		dist_ = sqrt(pow(msg->pose.position.x-current_target_.pose.position.x,2) + pow(msg->pose.position.y-current_target_.pose.position.y,2) + pow(msg->pose.position.z-current_target_.pose.position.z,2));
		
		// std::cout << dist_ << std::endl;
		// ROS_INFO_STREAM("begin_time_" << begin_time_);
		// ROS_INFO_STREAM("wait_time_" << wait_time_);
		// ROS_INFO_STREAM("current_time_" << ros::Time::now());

		if (ros::Time::now() > begin_time_ + wait_time_ && start_counting_){
			go_land_ = true;
			// ROS_INFO("go_land_ = true");
		};	

		if ( dist_ < tol_ && !start_counting_){
			ros::Time::now();
			begin_time_ = ros::Time::now();
			wait_time_ = ros::Duration(6);
			start_counting_ = true;
			// ROS_INFO("start_counting_ = true");
		}
		else if (dist_ > tol_){
			start_counting_ = false;
			// ROS_INFO("start_counting_ = false");
		}
	}

	// publisher setpoints
    void Control::pubPos(){
        //stream some initial points
        for(int i = 100; i > 0; --i){
            pos_pub_.publish(current_pos_);
            //ros::spinOnce();
            ros::Duration(20).sleep(); // set rate for sleeping
			ROS_INFO("publisher called");
        }
    }
} // end namespace
