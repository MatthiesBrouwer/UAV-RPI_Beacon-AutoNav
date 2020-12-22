# control_tello

## Intro
This package holds python scripts, c++ source and header files and launch files. The package can be used to control a dji TELLO drone. The tellopy package is used as bridge. 
 
### Launch files
There are 4 launch files, main.launch is used to start a connection with the drone.  

**main.launch**: it starts the `driver2.launch` and `start_ar_track_alvar.launch`. Next it opens one action client (`control` node) and two action servers (`takeoff_land` and `move_drone` nodes). From the package `control_rosparam` it starts the similar named node in a separate x-term. Also rviz is opened with a preset configuration in combination with some static publishers that simulate the orientatino of the camera.     

**start_ar_track_alvar.launch**: launches the artag tracking packages. Use the camera topics to post the found tags. 

**driver2.launch**: launches the `flock_driver.py`, which acts as a translation between tellopy and ros. 

**tello_description.launch**: needs fixing if a robotmodel is desired. 

### Source files 
There are 6 source files, 3 library and 3 nodes. 

**control.cpp**: describes the control class. Regularly checks if rosparameters are updated.  

**control_node.cpp**: the launches the control object which acts as a action client. 

**move_drone.cpp**: contains a class to get the transformation of the found artag. The tranformation is used to give new velocity objective for the drone. 

**move_drone_node.cpp**: the `move_drone` action server. It initializes an object of type "MoveDrone" and waits for calls from the client. 

**takeoff_land.cpp**: It can post an empty message on the /takeoff or /land topic.  

**takeoff_land_node.cpp**: the `takeoff_land` action server. Initializes an object of type `takeoff_land` and waits for a call. 

### Header files
There are 3 header files: **control.h**, **move_drone.h** and **takeoff_land.h**.

## ToDo
extra features can easily be added by adding an extra action server.


