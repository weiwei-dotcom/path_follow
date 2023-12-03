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
void getCDCRPointsAndTangentVector();
void discretePath();

private:
int path_follow_nanotime_interval;
double sample_interval;
double length;
std::vector<std::vector<Eigen::Vector2d>> joint_variates_at_max_deviation;
std::vector<double> max_deviations;
std::vector<double> cdcr_point_deviation_values;
// the element is the joint bone's points of each joint
Eigen::MatrixXd cdcr_points, cdcr_point_tangent_vectors;
Eigen::MatrixXd path_points;
int joint_number;
std::vector<Joint> joints;
std::vector<Eigen::Matrix4d> transform_joint_to_world;
Eigen::Matrix4d transform_base_to_world, transform_world_to_base;
int experience_type;
void path_follow_callback();

};

