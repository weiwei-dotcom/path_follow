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
void getPathDeviationAndNextIndex(const int path_point_index_start, 
                                  const int cdcr_point_index, 
                                  int& path_point_index_next_start);
private:
vector<double> cdcr_point_deviation_values;
Eigen::MatrixXd cdcr_points, cdcr_point_tangent_vectors;
Eigen::MatrixXd path_points;
int joint_number;
std::vector<Joint> joints;
std::vector<Eigen::Matrix4d> transform_joint_to_base;
Eigen::Matrix4d transform_base_to_world, transform_world_to_base;
rclcpp::Subscription<nav_msgs::msg::Path>::SharedPtr path_sub;


void path_follow_callback();


};

