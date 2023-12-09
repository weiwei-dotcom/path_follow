#include "rclcpp/rclcpp.hpp"
#include "joint.hpp"
#include "Eigen/Eigen"
#include "sophus/se3.hpp"
#include "nav_msgs/msg/path.hpp"
#include "uniform_bspline.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include <cmath>
#include <visualization_msgs/msg/marker_array.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <ceres/ceres.h>
#include <iostream>

class CDCR:public rclcpp::Node
{
public:
CDCR();
void getPathDeviationAndNextIndex(const int& path_point_index_start, 
                                  const int& cdcr_point_index, 
                                  int& path_point_index_next_start);
void getCDCRPointsAndTangentVector();
void discretePath();
void path_follow_exeperience();
void getCorrectTravelPointID();
void getBasePose();
bool baseDeviationCorrectCheck(const int& path_point_id);
bool baseDirectCorrectCheck(const int& path_point_id);
bool remainPathLengthCheck(const int& path_point_id);
double calVecProjValue(const Eigen::Vector3d& first_point, const Eigen::Vector3d& media_point, const Eigen::Vector3d& second_point);
Eigen::Vector3d getMediaInterPoint(const Eigen::Vector3d& inter_point,const Eigen::Vector3d& line_end1,const Eigen::Vector3d& line_end2);
void fitCDCR();
void path_follow();
void visualization();
struct x_residual{
    x_residual(double weight_position,
                double length_continuum,
                double length_rigid2,
                double x):
                     length_continuum_(length_continuum),
                     length_rigid2_(length_rigid2),
                     x_(x),
                     weight_position_(weight_position) {}
    template <typename T> bool operator()(const T* const alpha, const T* const theta, T* residual) const {
        residual[0] = weight_position_*(length_continuum_/theta*(1-cos(theta))*cos(alpha)+length_rigid2_*sin(theta)*cos(alpha)-x_);
        return true;
    }
private: 
    const double weight_position_;
    const double length_continuum_,length_rigid2_;
    const double x_; 
};
struct y_residual{
    y_residual(double weight_position,
                double length_continuum,
                double length_rigid2,
                double y):
                     length_continuum_(length_continuum),
                     length_rigid2_(length_rigid2),
                     y_(y),
                     weight_position_(weight_position) {}
    template <typename T> bool operator()(const T* const alpha, const T* const theta, T* residual) const {
        residual[0] = weight_position_*(length_continuum_/theta*(1-cos(theta))*sin(alpha)+length_rigid2_*sin(theta)*sin(alpha)-y_);
        return true;
    }
private: 
    const double weight_position_;
    const double length_continuum_,length_rigid2_;
    const double y_; 
};
struct z_residual{
    z_residual(double weight_position,
                double length_continuum,
                double length_rigid1,
                double length_rigid2,
                double z):
                     length_continuum_(length_continuum),
                     length_rigid1_(length_rigid1),
                     length_rigid2_(length_rigid2),
                     z_(z),
                     weight_position_(weight_position) {}
    template <typename T> bool operator()(const T* const alpha, const T* const theta, T* residual) const {
        residual[0] = weight_position_*(length_continuum_/theta*sin(theta)+length_rigid1_+length_rigid2_*cos(theta)-z_);
        return true;
    }
private: 
    const double weight_position_;
    const double length_continuum_,length_rigid2_,length_rigid1_;
    const double z_; 
};
struct angle_residual{
    angle_residual(double weight_direction,
                 double length_rigid1,
                 double length_continuum,
                 double length_rigid2,
                 Eigen::Vector3d tangent_vector):
                     length_rigid1_(length_rigid1), 
                     length_continuum_(length_continuum),
                     length_rigid2_(length_rigid2),
                     tangent_vector_(tangent_vector),
                     weight_direction_(weight_direction){}
    template <typename T> bool operator()(const T* const alpha, const T* const theta, T* residual) const {
        residual[0] = weight_direction_*acos(sin(theta)*cos(alpha)*tangent_vector_(0)
                                                +sin(theta)*sin(alpha)*tangent_vector_(1)
                                                +cos(theta)*tangent_vector_(2));
        return true;
    }
private: 
    const double weight_direction_;
    const double length_rigid1_,length_continuum_,length_rigid2_;
    const Eigen::Vector3d tangent_vector_; 
};
Eigen::Vector3d get_inter_point(const int& ratio_id, const int& total_id, const Eigen::Vector3d& start_point, const Eigen::Vector3d& end_point);
void cal_deviation_get_max_deviation_path_point_id();
void get_cdcr_sample_points();
void find_closed_path_point(const int& start_path_point_id,const Eigen::Vector3d& joint_end_position, int& segment_start_path_point_id);
private:
float base_box_color_r,base_box_color_g,base_box_color_b,base_box_color_a;
double base_box_size_x,base_box_size_y,base_box_size_z;
rclcpp::Publisher<visualization_msgs::msg::MarkerArray> cdcr_point_pub;
rclcpp::Publisher<visualization_msgs::msg::Marker> cdcr_base_pub;
rclcpp::Publisher<visualization_msgs::msg::MarkerArray> cdcr_plat_pub;
vector<int> cdcr_point_segment_id;
int fit_end_path_point_id;
int start_track_path_point_id;
double weight_position,weight_direction;
double bone_sample_interval;
rclcpp::TimerBase::SharedPtr timer;
double safe_path_length_redundance;
double base_tolerance_deviation, base_tolerance_angle_deviation;
Eigen::Vector3d base_path_point_end, base_path_point_start;
Eigen::Vector3d base_end_point,base_start_point;
Eigen::Vector3d base_z_axis,base_y_axis;
bool flag_discretized;
bool flag_end_experience;
bool flag_end_path_follow;
int track_path_point_id;
double post_line_path_length;
double arc_path_radius, arc_path_alpha, arc_path_theta;
int correct_start_path_point_id, correct_end_path_point_id;
int path_follow_nanotime_interval;
double sample_interval;
double length;
// Min radius of arc exprience
double min_arc_radius, max_arc_radius; 
// The times of follow the whole path

// TODO: Now we define the every path point's tangent vector with direction vector of previous point point to next point.
// Through observation we find that our maximum error is usually near the path shown in the figure below 
// We should send the variate of joint and path point to another function package to calculate the deviation 

// Every element is the max deviation of one path follow process
std::vector<double> max_deviation;
// path point index of max deviation with cdcr robot at one path follow process
std::vector<int> max_deviation_path_point_id;
// average time of one path follow process
std::vector<double> time_spend;
// joint bone's points of each joint
std::vector<Eigen::Vector3d> cdcr_points;
std::vector<Eigen::Vector3d> path_points;
int joint_number;
std::vector<Joint> joints;
std::vector<Eigen::Matrix4d> transform_joints_to_world, transform_world_to_joints;
Eigen::Matrix4d transform_base_to_world, transform_world_to_base;
int experience_type;

};

