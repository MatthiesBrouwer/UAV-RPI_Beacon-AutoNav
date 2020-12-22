/*
 * Author: bart 
 * Date: 21/10/2019
 */

// All declarations of variables and functions are described in the header.
#include <manual.h>

// The class definition is inside its namespace.
namespace manual_control{
	// Constructs instance of the class
	Control::Control(std::string name_server)
		:ac(name_server, true), 
		acs("start_node", true), 
		acl("land_drone", true),	
		// helper variables
		tol_(0.2),
		go_land_ (false),
		start_counting_(false),
		mode_has_been_set_(false),	
		once_(true) 
		{
    	ROS_INFO("waiting for all action servers to start.");
    	// action server call to start
    	ac.waitForServer();
    	ROS_INFO("move_drone server connected");
    	acs.waitForServer();
    	ROS_INFO("start server connected");
    	acl.waitForServer();
    	ROS_INFO("land_server server connected");
		
		// subscribers & timer
		pos_sub_ = nh_.subscribe("/mavros/local_position/pose", 10, &Control::currPos, this);	
		target_sub_ = nh_.subscribe("mavros/setpoint_position/local", 10, &Control::target, this);	
		state_sub_ = nh_.subscribe<mavros_msgs::State>("mavros/state", 10, &Control::state, this);	
		timer_t = nh_.createTimer(ros::Duration(0.2), &Control::periodicControl, this);
		
		// declare goals
    	goal_.follow = "ar_marker_13";
    	goal_mode_.mode = "OFFBOARD";
    	goal_land_.mode = "LAND";  
		}

	///////////////////// periodic control function ///////////////////////
	void Control::periodicControl(const ros::TimerEvent& event){	
		checkRosParam();

		// set mode with start server call
    	if ((current_state_.mode != "OFFBOARD" || !current_state_.armed) && !go_land_){
        	acs.sendGoal(goal_mode_);
        	ROS_INFO("goal send to start server");
        	acs.waitForResult();
        	ROS_INFO("mode set and armed");
			//sleep to wait so follow server can start??
     	  	ros::Duration(1.0).sleep();
			mode_has_been_set_ = true;
    	};
	
		// move_drone server call
    	//if (drone_state.current_state_.armed && drone_state.current_state_.mode == "OFFBOARD"){
	    if (mode_has_been_set_){
			ROS_INFO("ready to send goal to move drone");
    	//	ac.sendGoal(goal_, &Control::doneCb, &Control::activeCb, &Control::feedbackCb);
    		ac.sendGoal(goal_, 	boost::bind(&Control::doneCb, this, _1, _2));
			ROS_INFO("goal send to follow server");
			mode_has_been_set_ = false;
		}

		if (go_land_ && once_){
            //ROS_INFO("position reached");
            acl.sendGoal(goal_land_, boost::bind(&Control::doneLandingCb, this, _1, _2));
            once_ = false;
            ROS_INFO("goal for landing send");
        }
	}

	///////////////////////  callback functions ///////////////////////////
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
		// Calculate distance to next target point
 		dist_ = sqrt(	pow(msg->pose.position.x-current_target_.pose.position.x,2) 
						+ pow(msg->pose.position.y-current_target_.pose.position.y,2) 
						+ pow(msg->pose.position.z-current_target_.pose.position.z,2));
		if (ros::Time::now() > begin_time_ + wait_time_ && start_counting_)
			go_land_ = true;
		if ( dist_ < tol_ && !start_counting_){
			ros::Time::now();
			begin_time_ = ros::Time::now();
			wait_time_ = ros::Duration(30); //after 30 seconds landing is initiated
			start_counting_ = true;
		}
		else if (dist_ > tol_)
			start_counting_ = false;
	}

	void Control::checkRosParam(){
		if(ros::param::get("/land", go_land_)){
			//go_land_ = temp_string_;
		};
		if(ros::param::get("/move_drone", mode_has_been_set_)){
			//go_land_ = temp_string_;
		};
		//if(ros::param::get("/fly_circle", fly_circle_))
			//go_land_ = temp_string_;
	}

	/////////////////// action client callback function ////////////////////////////
	// Called once when the goal completes
	void Control::doneCb(const actionlib::SimpleClientGoalState& state, const aut_opp_msgs::MoveDroneResultConstPtr& result){
  		//ROS_INFO("Answer: done "/*%s", result->pos*/);
  		ros::shutdown();
	}

	// Called once when the goal becomes active
	void Control::doneLandingCb(const actionlib::SimpleClientGoalState& state, const aut_opp_msgs::StartResultConstPtr& result){
  		//if (result.SUCCEEDED)
		//	send acl.preempted(goal)
	}
} // end namespace
