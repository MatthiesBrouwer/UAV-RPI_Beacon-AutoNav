# px4_based

**important**: make sure to add the following lines in your .bashrc file. This allows gazebo to find the models quickly in the packages.

     export GAZEBO_MODEL_PATH=/home/boots/catkin_ws/src/sitl_gazebo/models:$GAZEBO_MODEL_PATH
     export GAZEBO_MODEL_PATH=/home/boots/catkin_ws/src/aut_opp/gazebo_model/models:$GAZEBO_MODEL_PATH

# intro
In the folder `px4_based` there are three packages: `aut_opp`, `aut_opp_msgs` and `fox_cart_description`.

The **aut_opp** packages contains the control nodes and launch files.

The **aut_opp_msgs** contains the action file that describe the messages for the action client and servers in the `aut_opp` package.

The **fox_cart_description** contains the urdf files that describe the fox cart from Dobots.

## How to use
Add the packages to your local catkin workspace and compile them. Make sure to have the necessary packages installed. To launch the simulation follow the example:
    
    open a new terminal run the lines behind the dollar signs. 
    $ roslaunch aut_opp simulation.launch
    $ roslaunch aut_opp control.launch
    Rviz and Gazebo will open the autopilot wil run in the background. The drone will take off and wait for the cart to move.
    
    The QGroudnControl station can be used to view the status of the drone and add waypoint manually or adjust the flightmode of the drone. The drone will only switch to certain modes if some conditions are met. It will only go to "OFFBOARD" is there is a stream of setpoints for example 
    $ ./QGroundControl.AppImage

    For a control interface of the fox cart the teleop twist package can be used.
    $ rosrun teleop_twist-keyboard teleop_twist_keyboard.py 
    this wll allow you to drive the fox cart. The drone will try to follow and position itself above the fox cart.


