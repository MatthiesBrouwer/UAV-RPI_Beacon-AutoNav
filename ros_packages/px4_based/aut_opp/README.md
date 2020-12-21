# aut_opp

**important**: make sure to add the following lines in your .bashrc file. This allows gazebo to find the models quickly in the packages.
	
	- export GAZEBO_MODEL_PATH=/home/boots/catkin_ws/src/sitl_gazebo/models:$GAZEBO_MODEL_PATH
	- export GAZEBO_MODEL_PATH=/home/boots/catkin_ws/src/aut_opp/gazebo_model/models:$GAZEBO_MODEL_PATH

## Intro
this package holds launch, source, header and world files. The package is can be used to control a UAV through the mavlink protocol. It aims to set the flight mode to "OFFBOARD" and then continue to search for artags to follow. It will send coordinates oft he found artags to the UAV. 
 
### Launch files
There are 6 launch files. There are two main launch files (control.launch and simulation.launch). 
	
**simulation.launch**: initiates three the three `start_*.launch` files + the px4 auto pilot. It sets the global world coordinates for the QGroundControl program. Use this launch file to start the simulation environment, the artag tracker and the mavros node.  

**control.launch**: starts one action client and two action servers. The action client will ask, the `"start_node"` action server, to change the flightmode of the drone to "OFFBOARD". The drone will be armed and take off to an initial height. 
The action client will ask the `move_drone` action server to follow the found artag. 
The callback function for the current position will update the boolean `go_land_` to true if the drone is in position for more then 6 seconds. The `land_drone` server will be called with the goal to land.   

**spawn_model.launch**: spawns an extra `fox_cart` in the simulation environment. Use a post fix to give different names in the simulation.
	_example_: `roslaunch aut_opp spawn_model.launch pf:="_1"` 
Change the `_1` to a custom additive. 

**start_ar_track_alvar.launch**: launches the artag tracking packages. Use the camera topics to post the found tags. 

**start_mavros.launch**: launches the mavros protocol. 

**start_roffa_world.launch**: starts the simulation environment in gazebo. The environment is simply a empty.world + and image of the 'stationplein' in Rotterdam. It spawns a 'iris + camera' drone and a fox cart in the world.

### Source files 
There are 6 source files, 3 library and 3 nodes. 

**control.cpp**: describes the control class, with two subscribers to get the state and position of the drone. These can be used in the control statements. 

**control_node.cpp**: the control action client, to call the `start` and `move_drone` action servers. 

**move_drone.cpp**: contains a class to get the transformation of the found artag. The tranformation is used to give new setpoints for the drone. 

**move_drone_node.cpp**: the `move_drone` action server. It initializes an object of type "MoveDrone" and waits for calls. 

**start.cpp**: based on the example from the px4 website. It loops until the mode of the drone is set to "OFFBOARD" and then arms the drone for take off. It gives an initial height to the drone. 

**start_node.cpp**: the `start` action server. Initializes an object of type "Start" and waits for a call. 

**land_drone.cpp**: It streams 20 times to set the mode of the drone to "LAND". It is subscribed to the current position of the artag. 

**land_drone_node.cpp**: the `land_drone` action server. Initializes an object of type "Land" and waits for a call. 

### Header files
There are 3 header files: **control.h**, **move_drone.h** and **start.h**.

### gazebo_model
In the folder **world**, the roffa.world file contains a physic block, adds a sun and places a roffa ground plane in the simulation.

The **models** folder holds 3 models. `iris_camera` takes the standard iris model from `sitl_gazebo` package and adds an `usb_camera` to the bottom. The `roffa` model is simply a collision box that acts as a ground plane with the `stationplein.jpg` as texture. `usb_camera` describes the camera use to locate the artags. The `iris_camera` and `usb_camera` package are copied from `mascor_uav_workshop` package. 


## ToDo
### Control node
Add all code from the the main to the class. Extra feedback can be used to determine if the drone still sees the artag otherwise land sequence should not be possible. Also and approach and search function should be nice. The `move_drone` server should be stopped when not used anymore. 


