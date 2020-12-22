# ros_packages

**important for px4_based simulation**: make sure to add the following lines in your .bashrc file. This allows gazebo to find the models quickly in the packages.
    
	 export GAZEBO_MODEL_PATH=/home/boots/catkin_ws/src/sitl_gazebo/models:$GAZEBO_MODEL_PATH
	 export GAZEBO_MODEL_PATH=/home/boots/catkin_ws/src/aut_opp/gazebo_model/models:$GAZEBO_MODEL_PATH

## intro
There are two main folders `px4_based` and `tello_dobots`. A detailed description in the folders README. 

**px4_based**

In the folder `px4_based` there are three packages: `aut_opp`, `aut_opp_msgs` and `fox_cart_description`.

**tello_dobots**

In the folder `tello_dobots` there are six packages: `camera_info_manager_py`, `control_rosparam`, `control_tello`, `control_tello_msgs`, `simulation_tello` and `tello_description`.





