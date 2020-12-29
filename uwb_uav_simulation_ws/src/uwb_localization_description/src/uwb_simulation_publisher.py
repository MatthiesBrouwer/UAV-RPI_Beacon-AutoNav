#!/usr/bin/env python  
import rospy

import math
import numpy as np
import tf2_ros

from uwb_localization_description.msg import uwb_data_raw
from gazebo_msgs.msg import ModelStates


import time
import threading
import os, sys
import random

global robot_pose_x,robot_pose_y,robot_pose_z
robot_pose_x =0
robot_pose_y =0
robot_pose_z =0

global counter
counter = 0



def get_anchors_pos():
	max_anchor = 100
	sensor_pos = []
	uwb_id = 'platform_prefix/uwb_anchor_'
	tf2_buffer = tf2_ros.Buffer()
	tf2_listener = tf2_ros.TransformListener(tf2_buffer)
	
		#--- Connect to the UWB anchors and save their distance to the robot ---#
	for i in range(max_anchor):
		try:
			time.sleep(0.3)
			trans = tf2_buffer.lookup_transform('map', uwb_id+str(i), rospy.Time(0))
			#trans = tf2_buffer.lookup_transform('map', 'base_link', rospy.Time(0))	
			sensor_pos.append([trans.transform.translation.x, trans.transform.translation.y,trans.transform.translation.z])
			print("New transform:\n X: {}\n Y: {} \n Z: {}".format(trans.transform.translation.x, trans.transform.translation.y,trans.transform.translation.z))
			print("==================================")
		except tf2_ros.LookupException:
			print("		!!!LOOKUP EXCEPTION!!!")
			break
		except tf2_ros.ConnectivityException:
			print("         !!!CONNECTIVITY  EXCEPTION!!!")
			break
		except tf2_ros.ExtrapolationException:
			print("         !!!EXTRAPOLATION EXCEPTION!!!")
			break

	#--- Transform the XYZ transforms to MM scale --#
	sensor_pos = np.dot(sensor_pos, 1000)
		
	if sensor_pos == []:
		rospy.logwarn("No anchors have been found. Functions is  working again.")
		get_anchors_pos()

	else:
		rospy.loginfo("UWB anchor list: \n Warning: uint is mm \n {}".format(str(sensor_pos)))

	return sensor_pos



def subscribe_data(ModelStates):
	#--- To get the real position of robot subscribe model states topic ---#
	global robot_pose_x, robot_pose_y, robot_pose_z
	global counter
	counter = counter + 1

	#--- gazebo/modelstate topic frequency is 100 hz. We descrese 10 hz with log method ---#
	if counter % 100 == 0:
		counter = 0
		
		#--- ModelStates.pose[2] = turtlebot3 model real position on modelstates ---#
		#robot_pose_x = ModelStates.pose[MODELSTATE_INDEX].position.x * 1000
		#robot_pose_y = ModelStates.pose[MODELSTATE_INDEX].position.y * 1000
		#robot_pose_z = ModelStates.pose[MODELSTATE_INDEX].position.z * 1000
		robot_pose_x = ModelStates.pose[MODELSTATE_INDEX].position.x * 1000
		robot_pose_y = ModelStates.pose[MODELSTATE_INDEX].position.y * 1000
		robot_pose_z = ModelStates.pose[MODELSTATE_INDEX].position.z * 1000

		


def calculate_distance(uwb_pose):
	global robot_pose_x, robot_pose_y, robot_pose_z
	robot_pose = [robot_pose_x, robot_pose_y, robot_pose_z]
	
	#--- describe 2 points ---#
	point_1 = np.array(uwb_pose)
	point_2 = np.array(robot_pose)
	
	#--- Calculate distance between the two points ---#
	total_distance = np.sum((point_1 - point_2)**2, axis = 0)
	
	#--- Add UWB noise ---#
	total_distance = total_distance + np.random.normal(0, total_distance * 0.015, 1)
	return np.sqrt(total_distance) 


def publish_data(destination_id_all, distance_all):
	uwb_data_cell = uwb_data_raw()
	uwb_data_cell.destination_id = destination_id_all
	uwb_data_cell.stamp = [rospy.Time.now(), rospy.Time.now(), rospy.Time.now()]
	uwb_data_cell.distance = distance_all
	#print("\nDISTANCES: {}".format(distance_all))
	pub.publish(uwb_data_cell)


if __name__ == '__main__':
	rospy.init_node('uwb_simulation_publisher', anonymous=True)
	pub = rospy.Publisher('uwb_data_topic', uwb_data_raw, queue_size=10)


	sensor_pos = []
	sensor_pos = get_anchors_pos()

	#--- Modelstate of robot is in case index 2 ---#
	MODELSTATE_INDEX = rospy.get_param('/uav_simulation_description/modelstate_index', 1)
	rospy.loginfo("{} is {}".format(rospy.resolve_name('uav_simulation_description/modelstate_index'), MODELSTATE_INDEX))
	r = rospy.Rate(10)
	time.sleep(0.5)

	#--- get robot real position => you can change ModelStates.pose[] different robot's ---#
	rospy.Subscriber('gazebo/model_states', ModelStates, subscribe_data)
	
	#--- Start publishing the UWB data ---#
	while not rospy.is_shutdown():
		distance_all = []
		destination_id_all = []

		for i in range(len(sensor_pos)):
			#--- Calculate the distance to the robot from all UWB anchors ---#
			distance = calculate_distance(sensor_pos[i])
			distance_all.append(distance)

		#--- publishe anchor names in same order ---#
		destination_id_all.append(0x694b)
		destination_id_all.append(0x6948)
		destination_id_all.append(0x694f)
		destination_id_all.append(0x694a)

		#--- Publish data with ros ---#
		publish_data(destination_id_all, distance_all)

		r.sleep()
	rospy.spin()

sys.exit()
