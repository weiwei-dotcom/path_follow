#include <iostream>
#include <Eigen/Eigen>


class Joint
{
public:
Joint();
Joint(double length_rigid1,double length_rigid2,double length_continuum);
std::vector<double> max_deviations;
std::vector<double> path_deviations;
std::vector<std::vector<Eigen::Vector2d>> joint_variate_at_max_deviation;
Eigen::MatrixXd joint_points,joint_points_tangent_vectors;
double length;
double length_rigid1,length_rigid2,length_continuum;
Eigen::Matrix4d transform;
private:
};
