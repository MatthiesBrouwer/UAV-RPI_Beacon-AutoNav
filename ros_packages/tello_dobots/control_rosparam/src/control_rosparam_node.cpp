#include <ros/ros.h>
//#include <iostream>

int main(int argc, char **argv){
	ros::init(argc, argv, "control_rosparam_node");
	std::string rosparam_name;
	bool true_or_false;
	
	std::cout << "|-----------------------------------------------|" << std::endl;
	std::cout << "|   example:                                    |" << std::endl;	
	std::cout << "|   type the name of your ros parameter         |" << std::endl;
	std::cout << "|   $ /ros_parameter_name                       |" << std::endl;	
	std::cout << "|   type the content for your rosparam (1 or 0) |" << std::endl;
	std::cout << "|   $ 1                                         |" << std::endl;
	std::cout << "|-----------------------------------------------|" << std::endl;
	std::cout << " " << std::endl;

	while(ros::ok()){
		//ROS_INFO("set a ros parameter");
		//ROS_INFO("type the name of the parameter make sure to add a '/' in front ");
		std::cout << "set the name of rosparam and content" << std::endl;
		std::cout << "enter the name of the parameter make sure to add a '/' in front \n";
		std::cin >> rosparam_name; 
		std::cout << "set the content of the parameter to 1 or 0  \n";
		std::cin >> true_or_false; 
		std::cout << " " << std::endl;
		std::cout << "rosparam: " << rosparam_name << "  content: " << true_or_false << std::endl;
		ros::param::set( rosparam_name, true_or_false);
		std::cout << "parameter is set" << std::endl;
		std::cout << " " << std::endl;
	}
	return 0;
}






