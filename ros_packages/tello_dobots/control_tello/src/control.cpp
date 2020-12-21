/*
 * Author: bart 
 * Date: 02/12/2019
 */

// All declarations of variables and functions are described in the header.
#include <control.h>

// The class definition is inside its namespace.
namespace manual_control{
	// Constructs instance of the class
	Control::Control(std::string name_server)
		: ac("move_drone", true), 
		acs("takeoff_land", true), 
		// helper variables
		takeoff_(false),
		land_(false),
		approach_(false),
		temp_bool_(false)
		{
    	ROS_INFO("waiting for all action servers to start.");
    	// action server call to start
    	ac.waitForServer();
    	ROS_INFO("move_drone server connected");
    	acs.waitForServer();
    	ROS_INFO("take off and land server connected");
		// subscribers & timer
		timer_t = nh_.createTimer(ros::Duration(0.2), &Control::periodicControl, this);
		// declare goals
    	goal_.follow = "ar_marker_8";
    	goal_takeoff_.mode = "/takeoff";
    	goal_land_.mode = "/land";  
		}

	///////////////////// periodic control function ///////////////////////
	void Control::periodicControl(const ros::TimerEvent& event){	
		checkRosParam();

		// set take off or land goal
    	if (takeoff_){
        	acs.sendGoal(goal_takeoff_);
        	ROS_INFO("goal send to start server");
        	acs.waitForResult();
     	  	ros::Duration(1.0).sleep();
			takeoff_ = false;
    	};
		if (land_){
            //ROS_INFO("position reached");
            acs.sendGoal(goal_land_, boost::bind(&Control::doneLandingCb, this, _1, _2));
            land_ = false;
            ROS_INFO("goal for landing send");
        };
		// move_drone server call
	    if (approach_){
    		//ac.sendGoal(goal_, &Control::doneCb, &Control::activeCb, &Control::feedbackCb);
    		ac.sendGoal(goal_, 	boost::bind(&Control::doneCb, this, _1, _2));
			ROS_INFO("goal send to follow server");
			approach_ = false;
		};
	}

	void Control::checkRosParam(){
		if(ros::param::get("/land", temp_bool_)){
			land_ = temp_bool_;
			ros::param::set("/land", 0);
			temp_bool_ = false;
		};
		if(ros::param::get("/takeoff", temp_bool_)){
			takeoff_ = temp_bool_;
			ros::param::set("/takeoff", 0);
			temp_bool_ = false;
		};
		if(ros::param::get("/approach", temp_bool_)){
			approach_ = temp_bool_;
			ros::param::set("/approach", 0);
			temp_bool_ = false;
		};
	}

	/////////////////// action client callback function ////////////////////////////
	// Called once when the goal completes
	void Control::doneCb(const actionlib::SimpleClientGoalState& state, const control_tello_msgs::MoveDroneResultConstPtr& result){
  		//ROS_INFO("Answer: done "/*%s", result->pos*/);
 		ros::shutdown();
	}

	// Called once when the goal becomes active
	void Control::doneLandingCb(const actionlib::SimpleClientGoalState& state, const control_tello_msgs::StartResultConstPtr& result){
  		//if (result.SUCCEEDED)
		//	send acl.preempted(goal)
	}
} // end namespace
