/*
 * Author: bart
 * Date: 26/08/2019
 *
This is source code for the move_drone node. 
 *
 */

#include <move_drone.h>

// The class definition is inside its namespace.
namespace move_drone{
	
	// constructor
	MoveDrone::MoveDrone(std::string name):
		as_(nh_, name, boost::bind(&MoveDrone::follow, this, _1), false), action_name_(name){
			// start action server
			as_.start();
			// Inside the constructor all variables/members are instantiatedy		
			pub_ = nh_.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local", 10); 
			// initial setpoint_ 
			setpoint_.header.frame_id = "home";
			setpoint_.pose.position.x = 0;
			setpoint_.pose.position.y = 0;
			setpoint_.pose.position.z = 4;
			stop_ = false;
			increase_height = false;
			reduce_height = false;
			Xd_ = 0;
			Yd_ = 0;
			tol_ = 0.5;
		}

	//callback function for the action server
	void MoveDrone::follow(const aut_opp_msgs::MoveDroneGoalConstPtr &goal){

		// action compute transform for artag
		while (stop_ == false ){
			// check that preempt has not been requested by the client
       		if (as_.isPreemptRequested() || !ros::ok()){
				as_.setPreempted();
  				stop_ = true;
	  		}
			
			try{
				ros::Time now = ros::Time::now();
				listener_.waitForTransform("/map", goal->follow , now, ros::Duration(2.0));
				listener_.lookupTransform("/map",  goal->follow , ros::Time(0), transform_);
				// update Xd & Yd
				Xd_ = std::abs(setpoint_.pose.position.x - transform_.getOrigin().x());
				Yd_ = std::abs(setpoint_.pose.position.y - transform_.getOrigin().y());
				// place X,Y in setpoint_
				setpoint_.pose.position.x = transform_.getOrigin().x();
				setpoint_.pose.position.y = transform_.getOrigin().y();
				feedback_.what = "SUCCES";
				result_.pos = "POSREACHED";
			}
			catch (tf::TransformException &ex){
				feedback_.what = ex.what();
				ros::Duration(1.0).sleep();
				result_.pos = "POSNOTREACHED";
			}
			as_.publishFeedback(feedback_);
			pub_.publish(setpoint_);
		}
		// set feedback and result
		ROS_INFO("end move_drone loop");
		as_.setSucceeded(result_);
	}
} // end namespace
