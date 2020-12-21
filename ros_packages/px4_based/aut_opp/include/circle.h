/*
 * Author: bart 
 * Date: 06/11/2019
 *
This is the header file of the circle node. Here the class definition is described and its variables/functions defined.
 *
 */

// This is for the compiler to check if this header file is already included, if not it is included.
#ifndef CIRCLE_H
#define CIRCLE_H

// include all necessary files, functions, and messages
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <math.h>
#include <stdlib.h>
// The class definition is inside the talker namespace. Namespaces are used. e collisions.
namespace circle{

	// Class definition
	class Circle{
	// This part is public and can be used by external users.
	// e.g. a public function/variable can be accesed using talker.test()
	  	public:
    // constructor definition
	    Circle();
	// member functions
		void pubb();
		void subb();
		void determineaction(const geometry_msgs::PoseStamped msgPose);

	// This part is private and can only be used by the class itself
	  	private:
	// attributes
    // according to styling conventions, all member variables have a
    // traling underscore.
		ros::NodeHandle nh_;
    	ros::Publisher circle_pub_; // publisher of new setpoint	
		ros::Subscriber subPosition_; //subscriber on current position
		
		float R_, Z_, tol_, alpha_;
		float Xd_, Yd_;
		int it_;
		geometry_msgs::PoseStamped pos_;
		geometry_msgs::PoseStamped setpoint_;
	}; // end class
} // end namespace

#endif // CIRCLE_H
