#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>


class Vica_joy_control
{
public:
  Vica_joy_control();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

  ros::NodeHandle nh_;

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;

};


Vica_joy_control::Vica_joy_control():
  linear_(1),
  angular_(2)
{

  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);


  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/vica_robot/mobile_base_controller/cmd_vel", 1);


  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &Vica_joy_control::joyCallback, this);

}

void Vica_joy_control::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist twist;
  twist.angular.z = a_scale_*joy->axes[angular_];
  twist.linear.x = l_scale_*joy->axes[linear_];
  vel_pub_.publish(twist);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "vica_joy_control");
  Vica_joy_control teleop_turtle;

  ros::spin();
}
