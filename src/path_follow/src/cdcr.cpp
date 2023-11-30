#include "cdcr.hpp"


CDCR::CDCR():Node("path_follow")
{
    this->declare_parameter<std::int16_t>("joint_number", 6);
    path_sub = this->create_subscription<nav_msgs::msg::Path>("path", 10, std::bind(&CDCR::path_callback, this, std::placeholders::_1));
    return;
}


void CDCR::path_callback(const nav_msgs::msg::Path::SharedPtr path_msg)
{
    return;
}