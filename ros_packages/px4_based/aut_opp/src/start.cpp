/*
 * Author: bart
 * Date: 23/08/2019
 *
 */

// All declarations of variables and functions are described in the header.
#include <start.h>

// The class definition is inside its namespace.
namespace start{
	// Constructs instance of the class
	Start::Start(std::string name):
		as_st_(nh_, name, boost::bind(&Start::setMode, this, _1), false) ,action_name_(name)
		{
		// start action server
        as_st_.start();
		// publishers & subscribers
		pub_ = nh_.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local",10); 
		state_sub_ = nh_.subscribe<mavros_msgs::State>("mavros/state", 1 ,&Start::state_, this);	
		
		// services
		ROS_INFO("wait for services");
		arming_client_ = nh_.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming"); 
		arming_client_.waitForExistence();
		set_mode_client_ = nh_.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");	
		set_mode_client_.waitForExistence();

		// set take off height used for stream offboard control point
		takeoff_point_.pose.position.x = 0;
		takeoff_point_.pose.position.y = 0;
		takeoff_point_.pose.position.z = 6;

		// set mode and arming
		arm_cmd_.request.value = true;	// set local to true for arming
		ROS_INFO("constructor fully finished");	
	}


	// Member functions
	void Start::state_(const mavros_msgs::State::ConstPtr& msg){
    	current_state_ = *msg;
	}
	
	void Start::setMode(const aut_opp_msgs::StartGoalConstPtr &goal){
	 	// mode is send by goal
		offb_set_mode_.request.custom_mode = goal->mode;
		ros::Rate rate_(25); // set rate for sleeping
		
		//stream some initial points
		for(int i = 30; ros::ok() && i > 0; --i){
            pub_.publish(takeoff_point_);
            //ros::spinOnce();
            rate_.sleep();
        }
		// keep track of time
		last_request_ = ros::Time::now(); 
		
		// start loop to enter requested mode
		while((current_state_.mode != goal->mode || !current_state_.armed)){
			if(current_state_.mode != goal->mode && (ros::Time::now() - last_request_ > ros::Duration(1.0))){
				if(set_mode_client_.call(offb_set_mode_) && offb_set_mode_.response.mode_sent)
                	ROS_INFO("mode has been set");
            	last_request_ = ros::Time::now();
			}
			else{
				if( !current_state_.armed && (ros::Time::now() - last_request_ > ros::Duration(1.0))){
                	if( arming_client_.call(arm_cmd_) && arm_cmd_.response.success)
                    	ROS_INFO("Vehicle armed");
                	last_request_ = ros::Time::now();
				}
			}
			pub_.publish(takeoff_point_);	
        	rate_.sleep();
		}
	 	feedback_.what = "mode is set and vehicle is armed";
        as_st_.publishFeedback(feedback_);
        result_.mode_set = "true";
        as_st_.setSucceeded(result_);
	}
} // end namespace
