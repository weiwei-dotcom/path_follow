#include "cdcr.hpp"


CDCR::CDCR():Node("path_follow")
{
    this->joint_number = -1;
    this->declare_parameter<std::int16_t>("joint_number", this->joint_number);
    if (joint_number == -1)
    {
        std::cout << "joint_number haven't initialized" <<std::endl;
        return;
    }
    for (int i=0;i<joint_number;i++)
    {
        this->transform_joint_to_base.push_back(Eigen::Matrix4d::Identity());
    }
    for (int i=0;i<20;i++)
    {
        this->declare_parameter<std::double_t>(std::string("joint") + std::to_string(i)+std::string("_rigid1_length"), -1.0);
        this->declare_parameter<std::double_t>(std::string("joint") + std::to_string(i)+std::string("_rigid2_length"), -1.0);
        this->declare_parameter<std::double_t>(std::string("joint") + std::to_string(i)+std::string("_continuum_length"), -1.0);
    }
    // Get the parameter of each joint;
    for (int i=0;i<joint_number;i++)
    {  
        Joint temp_joint(this->get_parameter(std::string("joint")+std::to_string(i)+std::string("_rigid1_length")).as_double(),
                         this->get_parameter(std::string("joint")+std::to_string(i)+std::string("_rigid2_length")).as_double(),
                         this->get_parameter(std::string("joint")+std::to_string(i)+std::string("_continuum_length")).as_double());
        for (int j=i+1;j<joint_number;j++)
        {
            this->transform_joint_to_base[j] = this->transform_joint_to_base[j]*temp_joint.getTransform();
        }
        this->joints.push_back(temp_joint);
    };
    this->transform_base_to_world = Eigen::Matrix4d::Identity();
    this->transform_world_to_base = Eigen::Matrix4d::Identity();
    path_sub = this->create_subscription<nav_msgs::msg::Path>("path", 10, std::bind(&CDCR::path_callback, this, std::placeholders::_1));
    return;
}

void CDCR::path_callback()
{
    ;
    return;
}