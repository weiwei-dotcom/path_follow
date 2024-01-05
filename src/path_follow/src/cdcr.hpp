#include "rclcpp/rclcpp.hpp"
#include "joint.hpp"
#include "Eigen/Eigen"
#include "sophus/se3.hpp"
#include "sophus/so3.hpp"
#include "nav_msgs/msg/path.hpp"
#include "uniform_bspline.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include <cmath>
#include <visualization_msgs/msg/marker.hpp>
#include <std_msgs/msg/float64.hpp>
#include "cv_bridge/cv_bridge.h"
#include <opencv2/opencv.hpp>
#include <ceres/ceres.h>
#include <iostream>
#include <fstream>


class CDCR:public rclcpp::Node
{
public:
typedef visualization_msgs::msg::Marker visualization_marker;
typedef visualization_msgs::msg::MarkerArray visualization_marker_array;
CDCR();
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
void path_follow(double& time_spend, double& max_deviation);
void visualization();
void show_max_deviations(const std::vector<double>& max_deviations, const std::vector<int>& max_deviation_path_point_ids);
struct position_residual{
    position_residual(double weight_position,
                double length_continuum,
                double length_rigid2,
                double length_rigid1,
                Eigen::Vector3d position
                ):
                     length_continuum_(length_continuum),
                     length_rigid2_(length_rigid2),
                     length_rigid1_(length_rigid1),
                     position_(position),
                     weight_position_(weight_position) {}
    template <typename T> bool operator()(const T* const alpha, const T* const theta, T* residual) const {
        residual[0] = weight_position_*(length_continuum_/theta[0]*(1.0-cos(theta[0]))*cos(alpha[0])+length_rigid2_*sin(theta[0])*cos(alpha[0])-position_.x());
        residual[1] = weight_position_*(length_continuum_/theta[0]*(1.0-cos(theta[0]))*sin(alpha[0])+length_rigid2_*sin(theta[0])*sin(alpha[0])-position_.y());
        residual[2] = weight_position_*(length_continuum_/theta[0]*sin(theta[0])+length_rigid1_+length_rigid2_*cos(theta[0])-position_.z());
        return true;
    }
private: 
    const double weight_position_;
    const double length_continuum_,length_rigid2_,length_rigid1_;
    const Eigen::Vector3d position_; 
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
        residual[0] = weight_direction_*180.0/M_PI*acos(sin(theta[0])*cos(alpha[0])*tangent_vector_(0)
                                                        +sin(theta[0])*sin(alpha[0])*tangent_vector_(1)
                                                        +cos(theta[0])*tangent_vector_(2));
        return true;
    }
private: 
    const double weight_direction_;
    const double length_rigid1_,length_continuum_,length_rigid2_;
    const Eigen::Vector3d tangent_vector_; 
};
Eigen::Vector3d get_inter_point(const int& ratio_id, const int& total_id, const Eigen::Vector3d& start_point, const Eigen::Vector3d& end_point);
void cal_deviation_get_max_deviation_path_point_id(double& max_deviation, int& max_deviation_path_point_ids);
void get_cdcr_sample_points();
void find_closed_path_point(const int& start_path_point_id,const Eigen::Vector3d& joint_end_position, int& segment_start_path_point_id);
void visualPathMarkers();
private:
std::ofstream per_radius_max_deviation_ofs;
std::ofstream per_radius_fit_time_ofs;
std::ofstream arc_radius_ofs;
std::ofstream per_fitperiod_max_deviation_ofs;
std::ofstream per_fitperiod_theta_value_ofs;
std::ofstream track_path_displacement_ofs;
// std::ofstream per_fitperiod_alpha_value_ofs;
int visualization_flag;
double arc_path_radius_step;
int sleep_nano_time;
rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr fit_time_pub;
rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr max_deviation_pub;
rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr deviation_marker_pub;

rclcpp::Publisher<visualization_marker>::SharedPtr cylinder1_obstacle_visualization_pub;
rclcpp::Publisher<visualization_marker>::SharedPtr cylinder2_obstacle_visualization_pub;

double deviation_marker_scale_x,deviation_marker_scale_y,deviation_marker_scale_z;
double deviation_marker_zoom_factor;
float base_box_color_r,base_box_color_g,base_box_color_b,base_box_color_a;
float cdcr_point_color_r,cdcr_point_color_g,cdcr_point_color_b,cdcr_point_color_a;
float cdcr_plat_color_r,cdcr_plat_color_g,cdcr_plat_color_b,cdcr_plat_color_a;
double base_box_size_x,base_box_size_y,base_box_size_z;
double cdcr_point_size_x,cdcr_point_size_y,cdcr_point_size_z;
double cdcr_plat_size_x,cdcr_plat_size_y,cdcr_plat_size_z;
double path_point_color_r,path_point_color_g,path_point_color_b,path_point_color_a;
double path_point_scale;
rclcpp::Publisher<visualization_marker>::SharedPtr path_point_markers_pub;
rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr cdcr_point_visualization_pub;
rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr base_visualization_pub;
rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr cdcr_plat_visualization_pub;
vector<int> cdcr_segment_point_id;
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
// joint bone's points of each joint
std::vector<Eigen::Vector3d> cdcr_points;
std::vector<Eigen::Vector3d> path_points;
int joint_number;
std::vector<Joint> joints;
std::vector<Eigen::Matrix4d> transform_joints_to_world, transform_world_to_joints;
Eigen::Matrix4d transform_base_to_world, transform_world_to_base;
int experience_type;
double alpha_lower_bound, alpha_upper_bound;
double theta_lower_bound, theta_upper_bound;
UniformBspline b_spline_path;
double time_interval;
std::vector<Eigen::Vector3d> temp_b_spline_path_interval_poins;
std::vector<Eigen::Vector3d> b_spline_path_interval_points, b_spline_start_end_derivatives;

//debug
rclcpp::Publisher<visualization_marker>::SharedPtr temp_b_spline_interval_points_pub;

//debug: find why the fit result change so extremelly
bool flag_first_fit;
int flag_visualize_b_spline_marker;
double theta_change_thresh;

double cylinder1_scale_x, cylinder1_scale_y, cylinder1_scale_z;
double cylinder2_scale_x, cylinder2_scale_y, cylinder2_scale_z;
double cylinder1_color_r, cylinder1_color_g, cylinder1_color_b;
double cylinder2_color_r, cylinder2_color_g, cylinder2_color_b;
double cylinder1_position_x, cylinder1_position_y, cylinder1_position_z;
double cylinder2_position_x, cylinder2_position_y, cylinder2_position_z;
double cylinder1_axis_x, cylinder1_axis_y, cylinder1_axis_z;
double cylinder2_axis_x, cylinder2_axis_y, cylinder2_axis_z;

double hole_scale_x,hole_scale_z;

double hole1_position_x,hole1_position_y,hole1_position_z;

double hole2_position_x,hole2_position_y,hole2_position_z;

double board_up_down_color_r,board_up_down_color_g,board_up_down_color_b;
double board_left_right_color_r,board_left_right_color_g,board_left_right_color_b;

double board_up_down_scale_x,board_up_down_scale_y,board_up_down_scale_z;
double board_left_right_scale_x,board_left_right_scale_y,board_left_right_scale_z;

rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr board_left_right_pub;
rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr board_up_down_pub;
};

