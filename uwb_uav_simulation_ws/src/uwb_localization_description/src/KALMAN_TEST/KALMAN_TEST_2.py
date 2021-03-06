#!/usr/bin/env python
'''
__author__ = "Bekir Bostanci"
__license__ = "BSD"
__version__ = "0.0.1"
__maintainer__ = "Bekir Bostanci"
__email__ = "bekirbostanci@gmail.com"
'''

import rospy 

import numpy as np
import scipy.stats 

from nav_msgs.msg import Odometry
from geometry_msgs.msg import Pose
from uav_simulation_description.msg import  uwb_data_raw
import math

import tf 
import tf2_ros
import time


#initialize belief
global mu 
mu = [0,0,0, 0.0]
global sigma 
sigma = np.array([[1.0, 0.0, 0.0],[0.0, 1.0, 0.0],[0.0, 0.0, 1.0]])
sensor_pos=[]

rospy.init_node('kalman_filter_localization', anonymous=True)
pub = rospy.Publisher('localization_data_topic', Pose, queue_size=10)
r = rospy.Rate(1)


def prediction_step(Odometry):
    global mu
    global sigma
    # Updates the belief, i.e., mu and sigma, according to the motion 
    # model
    # 
    # mu: 3x1 vector representing the mean (x,y,theta) of the 
    #     belief distribution
    # sigma: 3x3 covariance matrix of belief distribution 
    
    x = mu[0]
    y = mu[1]
    z = mu[2]
    theta = mu[3]

    delta_vel = Odometry.twist.twist.linear.x *1000           # redefine r1                  odom=>twist=>linear=>x 
    delta_w = Odometry.twist.twist.angular.z                  # redefine t                   odom=>twist=>angular=>z
    
    noise = 0.1**2
    v_noise = delta_vel**2
    w_noise = delta_w**2

    sigma_u = np.array([[noise + v_noise, 0.0],[0.0, noise + w_noise]])
    
    B = np.array([[np.cos(theta), 0.0],[np.sin(theta), 0.0],[0.0, 1.0]])


    #noise free motion
    x_new = x + delta_vel*np.cos(theta)/30
    y_new = y + delta_vel*np.sin(theta)/30
    z_new = z + delta_vel*np.tan(theta)/30

    theta_new = theta + delta_w/30
    
    #Jakobian of g with respect to the state
    G = np.array([[1.0, 0.0, -delta_vel * np.sin(theta)],
                    [0.0, 1.0, delta_vel * np.cos(theta)],
                    [0.0, 0.0, 1.0]])
    

    
    #new mu and sigma
    mu = [x_new, y_new, z_new, theta_new]
    sigma = np.dot(np.dot(G, sigma), np.transpose(G)) + np.dot(np.dot(B, sigma_u), np.transpose(B))

    #publish data every odom step 
    publish_data(mu[0],mu[1], mu[2])
    
    return mu,sigma


def correction_step(uwb_data,  sensor_pos):
    global mu
    global sigma
    # updates the belief, i.e., mu and sigma, according to the
    # sensor model
    # 
    # The employed sensor model is range-only
    #
    # mu: 3x1 vector representing the mean (x,y,theta) of the 
    #     belief distribution
    # sigma: 3x3 covariance matrix of belief distribution 

    x = mu[0]
    y = mu[1]
    z = mu[2] 
    theta = mu[3]

    #measured landmark ids and ranges
    ids = uwb_data.destination_id
    ranges =uwb_data.distance
    # Compute the expected range measurements for each landmark.
    # This corresponds to the function h
    H = []
    Z = []
    expected_ranges = []
    for i in range(len(ids)):
        lm_id = ids[i]
        meas_range = ranges[i]
        lx = sensor_pos[i][0]
        ly = sensor_pos[i][1]
        lz = sensor_pos[i][2]
        #calculate expected range measurement
        range_exp = np.sqrt( (lx - x)**2 + (ly - y)**2+(lz - z)**2 )
        #compute a row of H for each measurement
        H_i = [(x - lx)/range_exp, (y - ly)/range_exp, (z - lz)/range_exp]
        H.append(H_i)
        Z.append(ranges[i])
        expected_ranges.append(range_exp)
    # noise covariance for the measurements
    R = 0.5 * np.eye(len(ids))
    # Kalman gain
    K_help = np.linalg.inv(np.dot(np.dot(H, sigma), np.transpose(H)) + R)
    K = np.dot(np.dot(sigma, np.transpose(H)), K_help)
    # Kalman correction of mean and covariance
    mu = mu + np.dot(K, (np.array(Z) - np.array(expected_ranges)))
    sigma = np.dot(np.eye(len(sigma)) - np.dot(K, H), sigma)

    return mu,sigma


def subscribe_odom_data(Odometry):
    [mu,sigma]=prediction_step(Odometry)


def subscribe_uwb_data(uwb_data):
    [mu,sigma]=correction_step(uwb_data,  sensor_pos)


def publish_data(pose_x,pose_y, pose_z):
    robot_pos = Pose()
    robot_pos.position.x = float(pose_x)
    robot_pos.position.y = float(pose_y)
    robot_pos.position.z = float(pose_z)

    robot_pos.orientation.x = 0.0
    robot_pos.orientation.x = 0.0
    robot_pos.orientation.x = 0.0
    robot_pos.orientation.w = 0.0
    pub.publish(robot_pos)
    print("NEW POS: {}, {}, {}".format(robot_pos.position.x, robot_pos.position.y, robot_pos.position.z))



def get_anchors_pos():
        max_anchor = 100
        sensor_pos = []
        uwb_id = 'platform_prefix/uwb_anchor_'
        tf2_buffer = tf2_ros.Buffer()
        tf2_listener = tf2_ros.TransformListener(tf2_buffer)

        rate = rospy.Rate(10.0)


        #--- Connect to the UWB anchors and save their distance to the robot ---#
        for i in range(max_anchor):
                try:
                        time.sleep(0.3)
                        trans = tf2_buffer.lookup_transform('base_link', uwb_id+str(i), rospy.Time(0))
                        #trans = tf2_buffer.lookup_transform('map', 'base_link', rospy.Time(0)) 
                        sensor_pos.append([trans.transform.translation.x, trans.transform.translation.y,trans.transform.translation.z])
                        print("New transform:\n X: {}\n Y: {} \n Z: {}".format(trans.transform.translation.x, trans.transform.translation.y,trans.transform.translation.z))
                        print("==================================")
                except tf2_ros.LookupException:
                        print("         !!!LOOKUP EXCEPTION!!!")
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


if __name__ == "__main__":
    #get uwb anchors postion
    sensor_pos = get_anchors_pos()
    
    rospy.Subscriber("odom", Odometry, subscribe_odom_data)
    rospy.Subscriber("/uwb_data_topic", uwb_data_raw, subscribe_uwb_data)

    rospy.spin()
