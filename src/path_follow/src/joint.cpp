#include "joint.hpp"

Joint::Joint(){}
Joint::Joint(double length_rigid1,double length_rigid2,double length_continuum)
{
    this->alpha = 1e-4;
    this->theta = 1e-4;
    this->length_rigid1 = length_rigid1;
    this->length_rigid2 = length_rigid2;
    this->length_continuum = length_continuum;
    this->length = length_continuum+length_rigid1+length_rigid2;
    this->transform = Eigen::Matrix4d::Identity();
    this->transform(2,3) = this->length_rigid1+this->length_rigid2+this->length_continuum;
    return;
}

Eigen::Matrix4d getTransform()
{
    this->transform = 
    return this->transform;
}

