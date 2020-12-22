# tello_dobots

## intro
In the folder `tello_dobots` there are six packages: `camera_info_manager_py`, `control_rosparam`, `control_tello`, `control_tello_msgs`, `simulation_tello` and `tello_description`.

The **camera_info_manager_py** package is added as a submodule to the git repository. It is used with the decoding of the `camera_info` message. The package is supposed to be used directly. 

The **control_rosparam** package has a simple node that can set ros parameters in a simple way. Teh ros parameters can be used to set a certain mode for the drone or simulation.

**control_tello** is used to control the tello drone. It holds a few nodes and launch files. To operate the drone simply roslaunch the `main.launch`.

The **control_tello_msgs** builds the messages and action files needed for the `control_tello` package. 

The **simulation_tello** describes an simulation environment in gazebo. The drone used in the simualtion is operated with an px4 autopilot, make sure the firmware is installed. The drone is an Iris with an forward orientated camera. Allthough the autopilot is not the same certain scenarios can be tested. To operate the drone in the gazebo simulation the `aut_opp` package in the `px4_based` folder can be used. TODO: fix the offset of artag frames in rviz. The `fox_cart_description package` is used to add a car with artag to the simulation.  

The **tello_description** needs fixing, but a mesh file is ther and the beginning of an urdf (copied from flock package).

## Installation `(needed for the flock_driver.py)`
(copied from the flock package)
Use your favorite Python package manager to set up Python 2.7 and the following packages, minimal required versions:

	- numpy 1.15.2
	- av 0.5.2
	- opencv-python 3.4.3.18
	- opencv-contrib-python 3.4.3.18
	- tellopy 0.5.0

## How to use
Add the packages to your local catkin workspace and compile them. Make sure to have the necessary packages installed. To launch the drone follow the example:

    open a new terminal run the lines behind the dollar signs.
	
	Turn the drone on. A wifi signal `TELLO-xxxx` will apear. 
	
	Connect to the wifi signal.

	$ roslaunch control_tello main.launch

    Rviz and a x-term (terminal) will open.
	
	The x-term screen can be used to send commands to the control. There are three options 
		- /takeoff
		- /land
		- /approach	(used to let the drone follow an artag)
	Fill in one of the rosparameters and press enter. Then enter a 1 for true or 0 for false. 

	
