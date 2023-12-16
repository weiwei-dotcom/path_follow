#include "cdcr.hpp"


int main(int argc,char** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<CDCR>();
    node->path_follow_exeperience();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}