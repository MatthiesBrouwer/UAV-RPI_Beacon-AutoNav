/*
 * Author: bart
 * Date: 19/08/2019
 *
This is source code of the circle node. Here the class Circle is constructed and its variables/functions defined. This class is responsible for publishing a new setpoint on the mavros topic to produce a circular path.
 *
 */

// All declarations of variables and functions are described in the header file: /include/circle/circle.h therefore it is included here.
#include <circle.h>

// The class definition is inside its namespace.
namespace circle{
	// Constructs instance of the class
	Circle::Circle(std::string name):
		as_(nh_, name, boostLLbind(&Circle::determineaction, this, 1_), false), 
		action_name_(name),
        R_(30), // radius of the circle
        Z_(4),  // flying heigth
		tol_(10), //tolerance set to 2m
		alpha_(M_PI/10),
		it_(0)
		{	
		// start action server
		as_.start();
		// Inside the constructor all variables/members are instantiatedy		
		circle_pub_ = nh_.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local", 10);
		// set initial goal
		setpoint_.pose.position.x = 0;  		
		setpoint_.pose.position.y = 0; 
		setpoint_.pose.position.z = Z_;
		// 
	}

	// Member functions
	void Circle::subb(){
		subPosition_ = nh_.subscribe("/mavros/local_position/pose", 10, &Circle::determineaction, this);
	}

	// callback function
	void Circle::determineaction(const geometry_msgs::PoseStamped msgPose){
		
		// action compute transform for artag
        while (stop_ == false && ros::ok()){
            // check that preempt has not been requested by the client
            if (as_.isPreemptRequested() || !ros::ok()){
                as_.setPreempted();
                stop_ = true;
            }

			try{
                ros::Time now = ros::Time::now();
                listener_.waitForTransform("/map", goal->name_artag , now, ros::Duration(2.0));
                listener_.lookupTransform("/map",  goal->name_artag , ros::Time(0), transform_);
                // update feedback
				feedback_.
                feedback_.x = transform_.getOrigin().x();
                feedback_.y = transform_.getOrigin().y();
                feedback_.z = transform_.getOrigin().z();
            }
            catch (tf::TransformException &ex){
                feedback_.what = ex.what();
            }

    
			Xd_ = std::abs(msgPose.pose.position.x - setpoint_.pose.position.x);
			Yd_ = std::abs(msgPose.pose.position.y - setpoint_.pose.position.y);
			if (Xd_ < tol_ && Yd_ < tol_){
				std::cout << "next set point and it ="<< it_ << std::endl;
        	   	setpoint_.pose.position.x = R_*cos(it_*alpha_);
          		setpoint_.pose.position.y = R_*sin(it_*alpha_);
           		setpoint_.pose.orientation.z = sin((it_+4)*alpha_*0.5);
           		setpoint_.pose.orientation.w = cos((it_+4)*alpha_*0.5);
				it_++;
        		if(it_ == 20)
            	    it_ = 0;
            }	
			circle_pub_.publish(setpoint_);	
		}

	}// end callback func
} // end namespace
