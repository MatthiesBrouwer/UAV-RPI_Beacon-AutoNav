#!/bin/bash

cd ~
. /ros_entrypoint.sh
. catkin_ws/devel_isolated/setup.bash
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:/projects/ros_packages/px4_based:/projects

rosrun search_target_description FLY_test_1.py
