/*
 * Author: bart
 * Date: 24/10/2019
 *
This is source code for the move_drone node. 
 *
 */

#include <land_drone.h>

// The class definition is inside its namespace.
namespace land_drone{
	
	// constructor
	Land::Land(std::string name):
		as_(nh_, name, boost::bind(&Land::land, this, _1), false), action_name_(name){
			// start action server
			as_.start();
			// get current position         
			pos_sub_ = nh_.subscribe("/mavros/local_position/pose", 10, &Land::currPos, this);
			// land msg
	        land_ = nh_.serviceClient<mavros_msgs::CommandTOL>("mavros/cmd/land");
			// set landing message fixed values
        	land_set_mode_.request.altitude = 0;
        	land_set_mode_.request.min_pitch = 0;
        	land_set_mode_.request.yaw = 0;
			//helper var
			pos_received_ = false;
			stop_ = false;
		}

 	// Position callback function
    void Land::currPos(const geometry_msgs::PoseStamped::ConstPtr& msg){
        //ROS_INFO_STREAM(": %f" << dist_);
        land_set_mode_.request.latitude = msg->pose.position.x;
        land_set_mode_.request.longitude = msg->pose.position.y;
		pos_received_ = true;
		// ROS_INFO("subscriber called and position updated");
    }


	void Land::land(const aut_opp_msgs::StartGoalConstPtr &goal){
		stop_ = true;
		int i = 0;
        while(stop_ || i > 20){
			// check that preempt has not been requested by the client
       		if (as_.isPreemptRequested() || !ros::ok()){
				//ROS_INFO("%s: Preempted"/*, action_name_.c_str()*/);
        		// set the action state to preempted
        		as_.setPreempted();
  				stop_ = false;
	  		};

			if (pos_received_){
        		if(land_.call(land_set_mode_) && land_set_mode_.response.success)
					i++;
			}
			ros::Duration(0.5).sleep(); // wait shortly until position is received
        }

		// set feedback and result
		feedback_.what = "easy sailing going down";
		result_.mode_set = "landing in progress";
		as_.publishFeedback(feedback_);
		as_.setSucceeded(result_);
	}// end function
} // end namespace
