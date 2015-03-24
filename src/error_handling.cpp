#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt8.h"


#include <sstream>


//variables for different errors

bool battery_empty;
bool imu_error;


void ArduinoErrorHandler (const std_msgs::UInt8 &msg)
{
	switch(msg.data)
	{
		case 1: battery_empty = true; break;
		case 2: imu_error = true; break;
		
		default: battery_empty = false; imu_error = false; break;
	}
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "error");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("error", 1000);
  ros::Subscriber arduino_errors = n.subscribe("arduino_error",1, &ArduinoErrorHandler);
  ros::Rate loop_rate(10);

  
  while (ros::ok())
  {
    
    std_msgs::String msg;
    std::stringstream ss;
    ss << " This is error_handler ";
    msg.data = ss.str();


    ROS_INFO("%s", msg.data.c_str());

  
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    
  }


  return 0;
}
