/*
 * Author: bart
 * Date: 21/10/2019
 */

#include <ros/ros.h>
#include <control.h>

// Called once when the goal completes
void doneCb(const actionlib::SimpleClientGoalState& state, const aut_opp_msgs::MoveDroneResultConstPtr& result){
  //ROS_INFO("Finished in state %s", state.toString().c_str());
  //ROS_INFO("Answer: done "/*%s", result->pos*/);
  ros::shutdown();
}

// Called once when the goal becomes active
void activeCb(){
  ROS_INFO("Goal just went active");
}

// Called every time feedback is received for the goal
void feedbackCb(const aut_opp_msgs::MoveDroneFeedbackConstPtr& feedback){
  //ROS_INFO("Got Feedback" /* %s", feedback->what*/);
}

int main(int argc, char **argv){
  	// Initialize ros
  	ros::init(argc, argv, "control_node");
	// make object to track drone state
	control_drone::Control drone_state(1);
	// helper var
	bool position_reached = false;
	
	// action client
	actionlib::SimpleActionClient<aut_opp_msgs::MoveDroneAction> ac("move_drone", true);
   	actionlib::SimpleActionClient<aut_opp_msgs::StartAction> acs("start_node", true);
	actionlib::SimpleActionClient<aut_opp_msgs::StartAction> acl("land_drone", true); // same msg as start 

 	ROS_INFO("waiting for all action servers to start.");
    // action server call to start
    ac.waitForServer();
    ROS_INFO("move_drone server connected");
	acs.waitForServer();
    ROS_INFO("start server connected");
	acl.waitForServer();
	ROS_INFO("land_server server connected");	
	
	//initialise with 
  	ros::Rate loop_rate(25); // rate of loop in Hz
	
	// declare goals
    aut_opp_msgs::MoveDroneGoal goal;    
 	goal.follow = "ar_marker_13";   	
 	aut_opp_msgs::StartGoal goal_mode;
    goal_mode.mode = "OFFBOARD";
	aut_opp_msgs::StartGoal goal_land;
	goal_land.mode = "LAND";
	
	// set mode
	if (drone_state.current_state_.mode != "OFFBOARD" || !drone_state.current_state_.armed){
		acs.sendGoal(goal_mode);
		ROS_INFO("goal send to follow server");
		acs.waitForResult();
		ROS_INFO("mode set and armed");
		ros::Duration(1.0).sleep();
	};

	// follow procedure
	//if (drone_state.current_state_.armed && drone_state.current_state_.mode == "OFFBOARD"){
		
	ROS_INFO("ready to send goal to move drone");
	ac.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
    ROS_INFO("goal send to follow server");
	bool once = true;
	// loop until terminated
  	while (ros::ok()){
		// now check if position is reached
		// std::cout << "go_land_ : "<< drone_state.go_land_ << std::endl;
		// std::cout << "start_counting_ : " << drone_state.start_counting_ << std::endl;

		if (drone_state.go_land_ && once ){
			//ROS_INFO("position reached");
			acl.sendGoal(goal_land);
			once = false;
			ROS_INFO("goal send");
		}
  		loop_rate.sleep(); 
		ros::spinOnce();
		//ros::spin();
	}
}
