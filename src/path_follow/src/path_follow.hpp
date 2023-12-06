#include "rclcpp/rclcpp.hpp"
#include "path_follow_interface/msg/interface.hpp"

class PathFollow:public rclcpp::Node
{
public: 
PathFollow();


private:
double path_sample_interval;
int move_period_interval;

};