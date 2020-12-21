#!/usr/bin/env python

import rospy
import math
import tf2_ros
import tf_conversions
import geometry_msgs

br = tf2_ros.TransformBroadcaster()

position_uav = [0., 0.]
position_platform = [0., 0.]


def get_tf():
	t = geometry_msgs.msg.TranfromStamped()
	

	
