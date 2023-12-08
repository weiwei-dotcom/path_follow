#include "rclcpp/rclcpp.hpp"
#include "joint.hpp"
#include "Eigen/Eigen"
#include "sophus/se3.hpp"
#include "nav_msgs/msg/path.hpp"
#include "uniform_bspline.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include <cmath>
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
    x_residual(double weight_postion,
                double length_continuum,
                double length_rigid2,
                double x):
                     length_continuum_(length_continuum),
                     length_rigid2_(length_rigid2),
                     x_(x),
                     weight_position_(weight_position) {}
    template <typename T> bool operator()(const T* const alpha, const T* const theta, T* residual) const {
        residual[0] = weight_position_*(pow(length_continuum_/theta*(1-cos(theta))*cos(alpha)+length_rigid2_*sin(theta)*cos(alpha)-position_(0),2));
        return true;
    }
private: 
    const double weight_position_,weight_direction_;
    const double length_rigid1_,length_continuum_,length_rigid2_;
    const double x_; 
};
//todo:
struct angle_residual{
    fit_residual(double weight_postion,
                 double weight_direction,
                 double length_rigid1,
                 double length_continuum,
                 double length_rigid2,
                 Eigen::Vector3d position,
                 Eigen::Vector3d tangent_vector):
                     length_rigid1_(length_rigid1), 
                     length_continuum_(length_continuum),
                     length_rigid2_(length_rigid2),
                     position_(position),
                     tangent_vector_(tangent_vector),
                     weight_position_(weight_postion),
                     weight_direction_(weight_direction){}
    template <typename T> bool operator()(const T* const alpha, const T* const theta, T* residual) const {
        residual[0] = weight_position_*(pow(length_continuum_/theta*(1-cos(theta))*cos(alpha)+length_rigid2_*sin(theta)*cos(alpha)-position_(0),2)
                                       +pow(length_continuum_/theta*(1-cos(theta))*sin(alpha)+length_rigid2_*sin(theta)*sin(alpha)-position_(1),2)
                                       +pow(length_continuum_/theta*sin(theta)+length_rigid1_+length_rigid2_*cos(theta)-position_(2), 2))
                      +weight_direction_*pow(acos(sin(theta)*cos(alpha)*tangent_vector_(0)
                                                  +sin(theta)*sin(alpha)*tangent_vector_(1)
                                                  +cos(theta)*tangent_vector_(2)),2);
        return true;
    }
private: 
    const double weight_position_,weight_direction_;
    const double length_rigid1_,length_continuum_,length_rigid2_;
    const Eigen::Vector3d position_,tangent_vector_; 
};
struct angle_residual{
    fit_residual(double weight_postion,
                 double weight_direction,
                 double length_rigid1,
                 double length_continuum,
                 double length_rigid2,
                 Eigen::Vector3d position,
                 Eigen::Vector3d tangent_vector):
                     length_rigid1_(length_rigid1), 
                     length_continuum_(length_continuum),
                     length_rigid2_(length_rigid2),
                     position_(position),
                     tangent_vector_(tangent_vector),
                     weight_position_(weight_postion),
                     weight_direction_(weight_direction){}
    template <typename T> bool operator()(const T* const alpha, const T* const theta, T* residual) const {
        residual[0] = weight_position_*(pow(length_continuum_/theta*(1-cos(theta))*cos(alpha)+length_rigid2_*sin(theta)*cos(alpha)-position_(0),2)
                                       +pow(length_continuum_/theta*(1-cos(theta))*sin(alpha)+length_rigid2_*sin(theta)*sin(alpha)-position_(1),2)
                                       +pow(length_continuum_/theta*sin(theta)+length_rigid1_+length_rigid2_*cos(theta)-position_(2), 2))
                      +weight_direction_*pow(acos(sin(theta)*cos(alpha)*tangent_vector_(0)
                                                  +sin(theta)*sin(alpha)*tangent_vector_(1)
                                                  +cos(theta)*tangent_vector_(2)),2);
        return true;
    }
private: 
    const double weight_position_,weight_direction_;
    const double length_rigid1_,length_continuum_,length_rigid2_;
    const Eigen::Vector3d position_,tangent_vector_; 
};
struct angle_residual{
    fit_residual(double weight_postion,
                 double weight_direction,
                 double length_rigid1,
                 double length_continuum,
                 double length_rigid2,
                 Eigen::Vector3d position,
                 Eigen::Vector3d tangent_vector):
                     length_rigid1_(length_rigid1), 
                     length_continuum_(length_continuum),
                     length_rigid2_(length_rigid2),
                     position_(position),
                     tangent_vector_(tangent_vector),
                     weight_position_(weight_postion),
                     weight_direction_(weight_direction){}
    template <typename T> bool operator()(const T* const alpha, const T* const theta, T* residual) const {
        residual[0] = weight_position_*(pow(length_continuum_/theta*(1-cos(theta))*cos(alpha)+length_rigid2_*sin(theta)*cos(alpha)-position_(0),2)
                                       +pow(length_continuum_/theta*(1-cos(theta))*sin(alpha)+length_rigid2_*sin(theta)*sin(alpha)-position_(1),2)
                                       +pow(length_continuum_/theta*sin(theta)+length_rigid1_+length_rigid2_*cos(theta)-position_(2), 2))
                      +weight_direction_*pow(acos(sin(theta)*cos(alpha)*tangent_vector_(0)
                                                  +sin(theta)*sin(alpha)*tangent_vector_(1)
                                                  +cos(theta)*tangent_vector_(2)),2);
        return true;
    }
private: 
    const double weight_position_,weight_direction_;
    const double length_rigid1_,length_continuum_,length_rigid2_;
    const Eigen::Vector3d position_,tangent_vector_; 
};
//TODO:

private:
ceres::Problem fit_problem;
ceres::Solver::Options option;
ceres::Solver::Summary summary;
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
int start_track_path_point_id;
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
// path point index of max deviation with cdcr robot at one path follow
std::vector<int> max_deviation_path_point_id;
// average time of one path follow process
std::vector<double> time_spend;
// The distribution of the deviation at each cdcr point on one track process
std::vector<double> cdcr_point_deviation;
// // The max deviation cdcr point id of cdcr point on one track process
// int max_deviation_cdcr_point_id;

// joint bone's points of each joint
std::vector<Eigen::Vector3d> cdcr_point_positions, cdcr_point_tangent_vectors;
std::vector<Eigen::Vector3d> path_points;
int joint_number;
std::vector<Joint> joints;
std::vector<Eigen::Matrix4d> transform_joints_to_world, transform_world_to_joints;
Eigen::Matrix4d transform_base_to_world, transform_world_to_base;
int experience_type;

};

