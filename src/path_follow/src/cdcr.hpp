#include "rclcpp/rclcpp.hpp"
#include "joint.hpp"
#include "Eigen/Eigen"
#include "sophus/se3.hpp"
#include "nav_msgs/msg/path.hpp"
#include <iostream>

class CDCR:public rclcpp::Node
{
public:
CDCR();

private:
std::vector<Joint> joints;
std::vector<Eigen::Matrix4d> transform_base_to_joint;
Eigen::Matrix4d transform_base_to_world, transform_world_to_base;
rclcpp::Subscription<nav_msgs::msg::Path>::SharedPtr path_sub;


void path_callback(const nav_msgs::msg::Path::SharedPtr path_msg);


};

