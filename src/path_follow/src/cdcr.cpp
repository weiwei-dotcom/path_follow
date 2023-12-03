#include "cdcr.hpp"


CDCR::CDCR():Node("path_follow")
{
    this->sample_interval = -1.0;
    this->joint_number = -1;
    this->declare_parameter<std::double_t>("sample_interval", this->sample_interval);
    this->declare_parameter<std::int16_t>("joint_number", this->joint_number);
    if (joint_number == -1)
    {
        std::cout << "joint_number haven't initialized" <<std::endl;
        return;
    }
    for (int i=0;i<joint_number;i++)
    {
        this->transform_joint_to_world.push_back(Eigen::Matrix4d::Identity());
    }
    for (int i=0;i<20;i++)
    {
        this->declare_parameter<std::double_t>(std::string("joint") + std::to_string(i)+std::string("_rigid1_length"), -1.0);
        this->declare_parameter<std::double_t>(std::string("joint") + std::to_string(i)+std::string("_rigid2_length"), -1.0);
        this->declare_parameter<std::double_t>(std::string("joint") + std::to_string(i)+std::string("_continuum_length"), -1.0);
    }
    for (int i=0;i<joint_number;i++)
    {  
        Joint temp_joint(this->get_parameter(std::string("joint")+std::to_string(i)+std::string("_rigid1_length")).as_double(),
                         this->get_parameter(std::string("joint")+std::to_string(i)+std::string("_rigid2_length")).as_double(),
                         this->get_parameter(std::string("joint")+std::to_string(i)+std::string("_continuum_length")).as_double());
        for (int j=i+1;j<joint_number;j++)
        {
            this->transform_joint_to_world[j] = this->transform_joint_to_world[j]*temp_joint.transform;
        }
        this->joints.push_back(temp_joint);
    };
    this->transform_base_to_world = Eigen::Matrix4d::Identity();
    this->transform_world_to_base = Eigen::Matrix4d::Identity();
    this->path_follow_nanotime_interval = -1.0;
    this->declare_parameter("path_follow_nanotime_interval", this->path_follow_nanotime_interval);
    std::cout << "here may cause error: 40" << std::endl;
    auto time = this->create_wall_timer(std::chrono::nanoseconds(path_follow_nanotime_interval),
                                        std::bind(&CDCR::path_follow_callback,this));
    this->experience_type = -1;
    this->declare_parameter("experience_type", this->experience_type);
    return;
}

void CDCR::path_follow_callback()
{
    // discrete the path
    discretePath();
    return;
}

void CDCR::discretePath()
{
    switch (this->experience_type)
    {
    // case 1 is using the conbination of line and circle;
    case 1:
        
        break;

    // default is using the B-spline;
    default:
    
        break;
    }
    return;
}

void CDCR::getCDCRPointsAndTangentVector()
{
    for (int i=0;i<this->joint_number;i++)
    {
        for (int j =0;j<joints[i].joint_points.size();j++)
        {

        }
    }
    return;
}

// Calculate the deviation of with path, which the deviation is the distance 
// between cdcr_point and the point of intersection of cdcr_point's norm plane and path
void CDCR::getPathDeviationAndNextIndex(const int path_point_index_start, 
                                        const int cdcr_point_index, 
                                        int& path_point_index_next_start)
{
    int temp_index = path_point_index_start;
    Eigen::Vector3d direction = this->cdcr_points.col(cdcr_point_index)-this->path_points.col(temp_index);
    std::cout << "here may cause error of eigen vector" << std::endl;
    double direction_value = this->cdcr_point_tangent_vectors.col(cdcr_point_index).dot(direction);
    if (direction_value < 0)
    {
        temp_index -= 1;
        for (int i=temp_index; i>=0; i--)
        {
            Eigen::Vector3d last_direction = direction;
            double last_direction_value = direction_value;
            direction=this->cdcr_points.col(cdcr_point_index)-this->path_points.col(i);
            direction_value = this->cdcr_point_tangent_vectors.col(cdcr_point_index).dot(direction);
            if (direction_value > 0)
            {
                double temp_sum = direction_value + std::abs(last_direction_value);
                Eigen::Vector3d interpolated_point = (temp_sum-direction_value)/temp_sum * this->path_points.col(i)
                                                    +(direction_value/temp_sum) * path_points.col(i+1);
                this->cdcr_point_deviation_values[cdcr_point_index] = (interpolated_point-cdcr_points.col(cdcr_point_index)).norm();
                path_point_index_next_start = i+1;
                return;
            }
        }
    }
    else
    {
        temp_index += 1;
        int path_points_size = this->path_points.size();
        for (int i=temp_index; i<=path_points_size; i++)
        {
            Eigen::Vector3d last_direction = direction;
            double last_direction_value = direction_value;
            direction=this->cdcr_points.col(cdcr_point_index)-this->path_points.col(i);
            direction_value = this->cdcr_point_tangent_vectors.col(cdcr_point_index).dot(direction);
            if (direction_value < 0)
            {
                double temp_sum = last_direction_value + std::abs(direction_value);
                Eigen::Vector3d interpolated_point = (temp_sum-last_direction_value)/temp_sum * this->path_points.col(i-1)
                                                    +(last_direction_value/temp_sum) * path_points.col(i);
                this->cdcr_point_deviation_values[cdcr_point_index] = (interpolated_point-cdcr_points.col(cdcr_point_index)).norm();
                path_point_index_next_start = i;
                return;
            }
        }
    }
    return;
}