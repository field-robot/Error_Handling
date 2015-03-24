#include "ros/ros.h"
//#include "std_msgs/String.h"
#include "std_msgs/UInt8.h"


#include <sstream>


//variables for different errors

bool battery_empty;
bool imu_error;
bool laser_error_var;

void ArduinoErrorHandler (const std_msgs::UInt8 &msg)
{
	switch(msg.data)
	{
		case 1: battery_empty = true; break;
		case 2: imu_error = true; break;
		
		default: battery_empty = false; imu_error = false; break;
	}
}

void LaserErrorHandler(const std_msgs::UInt8 &msg)
{
	switch(msg.data)
	{
		case 1: laser_error_var = true;
		break;
		default:
		laser_error_var = false;
		break;
	}
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "error");
  ros::NodeHandle n;
  ros::Publisher errors = n.advertise<std_msgs::UInt8>("error", 1000);
  ros::Subscriber arduino_errors = n.subscribe("arduino_error",1, &ArduinoErrorHandler);
  ros::Subscriber laser_error = n.subscribe("lasererror",1,&LaserErrorHandler);
  ros::Rate loop_rate(10);

  
  while (ros::ok())
  {
    
    std_msgs::UInt8 msg;
    
    if (laser_error_var == true) 
    {
    msg.data = 255;
    }
    else msg.data = 0;
    


    ROS_INFO("%i", msg.data);

  
    errors.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    
  }


  return 0;
}
