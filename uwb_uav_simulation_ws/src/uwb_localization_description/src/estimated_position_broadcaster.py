#!/usr/bin/env python

import rospy
import math
import tf2_ros
import tf_conversions
import geometry_msgs
from uwb_localization_description.msg import position_data_uwb


br = tf2_ros.TransformBroadcaster()
cnt = 0
uav_position_estimate = []
platform_position = [3, 3, 0]

def calculate_tf(estimated_position):
	t = geometry_msgs.msg.TransformStamped()
	t.header.stamp = rospy.Time.now()
	t.header.frame_id = "map" 
	t.child_frame_id = "uav_position_estimate"
	t.transform.translation.x = estimated_position[0] + 3
	t.transform.translation.y = estimated_position[1] + 3
	t.transform.translation.z = estimated_position[2]
	q = tf_conversions.transformations.quaternion_from_euler(0,0,0)
	t.transform.rotation.x = q[0]
	t.transform.rotation.y = q[1]
	t.transform.rotation.z = q[2]
	t.transform.rotation.w = q[3]
	return t


def position_data_callback(position_msg):
	estimated_position = position_msg.uwb_position
	print("ESTIMATION OBTAINED: {}".format(estimated_position))
	estimated_transform = calculate_tf(estimated_position)
	print("ESTIMATED TRANSFORM: {}".format(estimated_transform))
	br.sendTransform(estimated_transform)


if __name__ == '__main__':
	rospy.init_node("uwb_estimate_tf_broadcaster")
	rate = rospy.Rate(10)

	rospy.Subscriber("/position_data_uwb", position_data_uwb, position_data_callback, queue_size = 10)
	

	rospy.spin()
