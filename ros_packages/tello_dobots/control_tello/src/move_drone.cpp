/*
 * Author: bart
 * Date: 02/12/2019
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
			pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 10); 
			// initial setpoint
			setpoint_.linear.x = 0;
			setpoint_.linear.y = 0;
			setpoint_.linear.z = 0;
			stop_ = false;
			increase_height = false;
			reduce_height = false;
		}

	void MoveDrone::steer(){
				// approach in the x-direction of base_link frame (forward direction)
				if (transform_.getOrigin().z() > 0.5){
					setpoint_.linear.x = 0.3;
				}
				else{
					setpoint_.linear.x = -0.1;
				};

				// position in the y-direction of the base_link frame (side ways)				
				if (transform_.getOrigin().x() > 0){
					setpoint_.linear.y = -0.2;
				}
				else{
					setpoint_.linear.y = 0.2;
				};
				// position in the y-direction of the base_link frame (up and down)				
				if (transform_.getOrigin().y() > 0.1){
					setpoint_.linear.z = -0.2;
				}
				else{
					setpoint_.linear.z = 0.2;
				};
	}

	//callback function for the action server
	void MoveDrone::follow(const control_tello_msgs::MoveDroneGoalConstPtr &goal){

		// action compute transform for artag
		while (stop_ == false ){
			// check that preempt has not been requested by the client
       		if (as_.isPreemptRequested() || !ros::ok()){
				as_.setPreempted();
  				stop_ = true;
	  		}
			
			try{
				ros::Time now = ros::Time::now();
				listener_.waitForTransform("/camera_link", goal->follow, now, ros::Duration(0.5));
				listener_.lookupTransform("/camera_link", goal->follow, ros::Time(0), transform_);
				ROS_INFO("transform found");
				// place X,Y in setpoint_
				//setpoint_.linear.x = transform_.getOrigin().x();
				//setpoint_.linear.y = transform_.getOrigin().y();
				MoveDrone::steer();	
				feedback_.what = "SUCCES";
				result_.pos = "POSREACHED";
			}
			catch (tf::TransformException &ex){
				ROS_INFO("no ar tag visible");
				setpoint_.linear.x = 0;
				feedback_.what = ex.what();
				ros::Duration(1.0).sleep();
				result_.pos = "POSNOTREACHED";
			}
			as_.publishFeedback(feedback_);
			pub_.publish(setpoint_);
			setpoint_.linear.x = 0;
			setpoint_.linear.y = 0;
			setpoint_.linear.z = 0;
			ros::Duration(0.5).sleep();	
			pub_.publish(setpoint_);
		}
		// set feedback and result
		ROS_INFO("end move_drone loop");
		as_.setSucceeded(result_);
	}
} // end namespace
