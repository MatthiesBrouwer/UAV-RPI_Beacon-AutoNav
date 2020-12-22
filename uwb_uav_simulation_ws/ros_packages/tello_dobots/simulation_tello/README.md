# simulation_tello

**important**: make sure to add the following lines in your .bashrc file. This allows gazebo to find the models quickly in the packages.
	
	- export GAZEBO_MODEL_PATH=/home/boots/catkin_ws/src/sitl_gazebo/models:$GAZEBO_MODEL_PATH
	- export GAZEBO_MODEL_PATH=/home/boots/catkin_ws/src/tello_dobots/simulation_tello/gazebo_model/models:$GAZEBO_MODEL_PATH

## Intro
A version of the iris drone with a front facing camera is added in this package. The `aut_opp` package can be used to control a the drone through the mavlink protocol. 
 
### Launch files
	
**simulation.launch**: Use this launch file to start the simulation environment, the artag tracker and the mavros node.  

### gazebo_model
In the folder **world**, the roffa.world file contains a physic block, adds a sun and places a roffa ground plane in the simulation.

The **models** folder holds 3 models. `iris_camera` takes the standard iris model from `sitl_gazebo` package and adds an `usb_camera` to the bottom. The `roffa` model is simply a collision box that acts as a ground plane with the `stationplein.jpg` as texture. `usb_camera` describes the camera use to locate the artags. The `iris_camera` and `usb_camera` package are copied from `mascor_uav_workshop` package. 

## ToDo

There is a small offset when the frames of a artag are visualized in rviz between the known location and the recognized location through the `ar_track_alvar` topic. This is likely due to some conversion in the tf tranformation or caused by the orientation of the camera in the urdf and the static tranformation of the `camera_link` to `base_link`. 
