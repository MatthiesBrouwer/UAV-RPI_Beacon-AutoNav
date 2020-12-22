/*
 * Author: bart
 * Date: 02/12/2019
 *
 */

// All declarations of variables and functions are described in the header.
#include <takeoff_land.h>

// The class definition is inside its namespace.
namespace takeoff_land{
	// Constructs instance of the class
	TakeOffLand::TakeOffLand(std::string name):
		as_st_(nh_, name, boost::bind(&TakeOffLand::setMode, this, _1), false) ,action_name_(name)
		{
		// start action server
        as_st_.start();
		// publishers & subscribers 
		///////////
		/////////// fix the right topic publisher
		///////////
		pub_takeoff_ = nh_.advertise<std_msgs::Empty>("/takeoff",10); 	
		pub_land_ = nh_.advertise<std_msgs::Empty>("/land",10); 
		ROS_INFO("constructor fully finished");	
	}

	void TakeOffLand::setMode(const control_tello_msgs::StartGoalConstPtr &goal){
	 	// mode is send by goal
		ros::Rate rate_(25); // set rate for sleeping
		ROS_INFO("goal has been received");

		// take_off
		if(goal->mode == "/takeoff"){
			pub_takeoff_.publish(empty_msg_);	
			ROS_INFO("take off has been set");
		}

		// land
		if(goal->mode == "/land"){
			pub_land_.publish(empty_msg_);	
			ROS_INFO("landing has been set");
		}

	 	feedback_.what = "mode is set";
        as_st_.publishFeedback(feedback_);
        result_.mode_set = "true";
        as_st_.setSucceeded(result_);
	}
} // end namespace
