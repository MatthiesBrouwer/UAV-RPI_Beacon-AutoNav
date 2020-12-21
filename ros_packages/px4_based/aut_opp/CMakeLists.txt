cmake_minimum_required(VERSION 2.8.3)
project(aut_opp)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
		gazebo_ros
		geometry_msgs
		mavros_msgs
		aut_opp_msgs
		actionlib_msgs
		roscpp
		roslib
		tf
		)

###################################
## catkin specific configuration ##
###################################
 catkin_package(
	CATKIN_DEPENDS actionlib_msgs aut_opp_msgs geometry_msgs mavros_msgs
	)

###########
## Build ##
###########

include_directories(
 	include
 	${catkin_INCLUDE_DIRS}
)

## Declare a C++ library

add_library(aut_opp 
			src/move_drone.cpp 
			src/start.cpp
			src/land_drone.cpp
			#src/control.cpp
			src/manual.cpp
)
target_link_libraries(aut_opp ${catkin_LIBRARIES})

## Declare a C++ executable
add_executable(move_drone_node src/move_drone_node.cpp)
add_dependencies(move_drone_node ${catkin_EXPORTED_TARGETS})
target_link_libraries(move_drone_node aut_opp ${catkin_LIBRARIES})
set_target_properties(move_drone_node PROPERTIES OUTPUT_NAME "move_drone")

add_executable(start_node src/start_node.cpp)
add_dependencies(start_node  ${catkin_EXPORTED_TARGETS})
target_link_libraries(start_node aut_opp ${catkin_LIBRARIES})
set_target_properties(start_node PROPERTIES OUTPUT_NAME "start")

add_executable(land_drone_node src/land_drone_node.cpp)
add_dependencies(land_drone_node  ${catkin_EXPORTED_TARGETS})
target_link_libraries(land_drone_node aut_opp ${catkin_LIBRARIES})
set_target_properties(land_drone_node PROPERTIES OUTPUT_NAME "land_drone")

#add_executable(control_node src/control_node.cpp)
#add_dependencies(control_node  ${catkin_EXPORTED_TARGETS})
#target_link_libraries(control_node aut_opp ${catkin_LIBRARIES})
#set_target_properties(control_node PROPERTIES OUTPUT_NAME "control")

add_executable(manual_node src/manual_node.cpp)
add_dependencies(manual_node  ${catkin_EXPORTED_TARGETS})
target_link_libraries(manual_node aut_opp ${catkin_LIBRARIES})
set_target_properties(manual_node PROPERTIES OUTPUT_NAME "manual")


