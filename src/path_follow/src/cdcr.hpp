#include "rclcpp/rclcpp.hpp"
#include "joint.hpp"
#include "Eigen/Eigen"
#include "sophus/se3.hpp"
#include "nav_msgs/msg/path.hpp"
#include "uniform_bspline.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include <iostream>

class CDCR:public rclcpp::Node
{
public:
CDCR();

private:
int joint_number;
std::vector<Joint> joints;
std::vector<Eigen::Matrix4d> transform_joint_to_base;
Eigen::Matrix4d transform_base_to_world, transform_world_to_base;
rclcpp::Subscription<nav_msgs::msg::Path>::SharedPtr path_sub;


void path_callback();


};

