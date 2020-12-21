#!/bin/bash

cd ~/catkin_ws
. devel_isolated/setup.bash

export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:/projects/ros_packages/px4_based:/projects
cd /PX4/Firmware
source Tools/setup_gazebo.bash $PWD $PWD/build/px4_sitl_default
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:$(pwd):$(pwd)/Tools/sitl_gazebo

cd /projects/


roslaunch search_target_description bringup_uav_rover.launch
