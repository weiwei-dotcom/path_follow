#include "joint.hpp"

Joint::Joint(){}
Joint::Joint(double length_rigid1,double length_rigid2,double length_continuum)
{
    this->length_rigid1 = length_rigid1;
    this->length_rigid2 = length_rigid2;
    this->length_continuum = length_continuum;
    this->transform = Eigen::Matrix4d::Identity();
    this->transform(2,3) = this->length_rigid1+this->length_rigid2+this->length_continuum;
    return;
}

Eigen::Matrix4d Joint::getTransform()
{
    return this->transform;
}

double Joint::getLengthRigid1()
{
    return this->length_rigid1;
}

double Joint::getLengthRigid2()
{
    return this->length_rigid2;
}

double Joint::getLengthContinuum()
{
    return this->length_continuum;
}
