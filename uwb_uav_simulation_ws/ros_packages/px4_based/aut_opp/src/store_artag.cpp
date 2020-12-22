/*
 * Author: bart
 * Date: 07/11/2019
 *
This is source code for the move_drone node. 
 *
 */

#include <store_artag.h>

// The class definition is inside its namespace.
namespace store{
	
	// constructor
	Store::Store(std::string name):
		as_(nh_, name, boost::bind(&Store::collect, this, _1), false), action_name_(name){
			// start action server
			as_.start();
			stop_ = false;
		}

	//callback function for the action server
	void Store::collect(const aut_opp_msgs::StoreArtagConstPtr &goal){

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
