#!/usr/bin/env python
import rospy
import math
import numpy as np
import time
from uwb_localization_description.msg import position_data_uwb
from uav_simulation_description.msg import uwb_data_raw
import threading
import os, sys



class triangulator_node_3D:
	def __init__(self, point_position_all):
		#--- Declare variables ---#
		self.uwb_data_raw_sub = rospy.Subscriber("/uwb_data_topic", uwb_data_raw, self.update_callback)
		self.pub = rospy.Publisher("/position_data_uwb", position_data_uwb, queue_size = 10)
		self.point_position_all = point_position_all
		self.point_distance_all = []

	#### Function: This  function return the current position estimation
	def get_position_estimation(self):
		return self.position_estimation



	def update_callback(self, uwb_data_raw_msg):
		#--- Save data obtained from topic ---#
		self.point_distance_all =  uwb_data_raw_msg.distance
		print("		NEW DATA OBTAINED: \n\t\tdistance: {}\n\t\tids: {}".format(self.point_distance_all, uwb_data_raw_msg.destination_id))
		

		#--- Recalculate measured position and publish result ---#
		self.position_estimation = self.triangulate_target_position()
		print("		NEW TRIANGULATION POSITION: {}".format(self.position_estimation))
		print("=================================\n\n")


	def triangulate_target_position(self):
		


	"""
	def triangulate_target_position(self):
		point_1 = np.array(self.point_position_all[0])
		point_2 = np.array(self.point_position_all[1])
		point_3 = np.array(self.point_position_all[2])
		point_4 = np.array(self.point_position_all[3])



		#point_1 = np.array(self.point_distance_all[0][:3])
		#point_2 = np.array(self.point_distance_all[1][:3])
		#point_3 = np.array(self.point_distance_all[2][:3])
		#point_4 = np.array(self.point_distance_all[3][:3])

		#radius_1 = distances_all[0][-1]
		#radius_2 = distances_all[1][-1]
		#radius_3 = distances_all[2][-1]
		#radius_4 = distances_all[3][-1]

		radius_1 = self.point_distance_all[0]
		radius_2 = self.point_distance_all[1]
		radius_3 = self.point_distance_all[2]
		radius_4 = self.point_distance_all[3]


		print("\n\n-----------------------")
		print("CALCULATIONS")
		print("\nRadius: {}, {}, {}, {}".format(radius_1, radius_2, radius_3, radius_4))


		e_x = (point_2 - point_1) / np.linalg.norm(point_2 - point_1)
		i = np.dot(e_x, (point_3 - point_1))

		e_y = (point_3 - point_1 - (i * e_x)) / (np.linalg.norm(point_3 - point_1 - (i * e_x)))

		e_z = np.cross(e_x, e_y)

		d = np.linalg.norm(point_2 - point_1)
		j = np.dot(e_y, (point_3 - point_1))
		x = ((radius_1**2) - (radius_2**2) + (d**2)) / (2*d)
		y = (((radius_1**2) - (radius_3**2) + (i**2) + (j**2)) / (2*j)) - ((i / j) * (x))

		z1 = np.sqrt(radius_1**2 - x**2 - y**2)
		z2 = np.sqrt(radius_1**2 - x**2 - y**2) * (-1)

		answer_1 = point_1 + (x * e_x) + (y * e_y) + (z1 * e_z)
		answer_2 = point_1 + (x * e_x) + (y * e_y) + (z2 * e_z)
		dist_1 = np.linalg.norm(point_4 - answer_1)
		dist_2 = np.linalg.norm(point_4 - answer_2)

		print("\n\n\tANSWER 1: {}\n\tANSWER 2: {}".format(answer_1, answer_2))

		if np.abs(radius_4 - dist_1) < np.abs(radius_4 - dist_2):
			return answer_1
		else:
			return answer_2
	"""

	def publish_data(self):
		new_position_data_uwb_msg = position_data_uwb()
		new_position_data_uwb_msg.uwb_position = self.position_estimation
		self.pub.publish(new_position_data_uwb_msg)


if __name__ == '__main__':
	#--- Initialize node ---#
	rospy.init_node('uwb_localization_publisher')
	r = rospy.Rate(10) #10hz

	#--- Initialize point positions. Change if changes are made to position distribution ---#
	point_position_all = [[-30, 30, 12],[30, 30, 12], [-30, -30, 12], [30, -30, 12]] 

	#--- Create 3d_triangulator_node object --#
	triangulator = triangulator_node_3D(point_position_all)

	while not rospy.is_shutdown():
		time.sleep(0.1)
		triangulator.publish_data()
	rospy.spin()

