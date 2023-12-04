#include "cdcr.hpp"


CDCR::CDCR():Node("path_follow")
{
    this->flag_end_path_follow = false;
    this->flag_discretized = false;
    this->declare_parameter<std::double_t>("sample_interval", 1.0);
    this->sample_interval = this->get_parameter("sample_interval").as_double();
    this->declare_parameter<std::int16_t>("joint_number", 8);
    this->joint_number = this->get_parameter("joint_number").as_int();
    this->declare_parameter<std::int16_t>("experience_type", this->experience_type);
    this->experience_type=this->get_parameter("experience_type").as_int();
    this->declare_parameter<std::double_t>("base_path_point_start_x", 0.0);
    this->base_path_point_start(0)=this->get_parameter("base_path_point_start_x").as_double();
    this->declare_parameter<std::double_t>("base_path_point_start_y", 0.0);
    this->base_path_point_start(1)=this->get_parameter("base_path_point_start_y").as_double();
    this->declare_parameter<std::double_t>("base_path_point_start_z", 0.0);
    this->base_path_point_start(2)=this->get_parameter("base_path_point_start_z").as_double();
    this->declare_parameter<std::double_t>("base_path_point_end_x", 0.0);
    this->base_path_point_end(0)=this->get_parameter("base_path_point_end_x").as_double();
    this->declare_parameter<std::double_t>("base_path_point_end_y", 1000.0);
    this->base_path_point_end(1)=this->get_parameter("base_path_point_end_y").as_double();
    this->declare_parameter<std::double_t>("base_path_point_end_z", 0.0);
    this->base_path_point_end(2)=this->get_parameter("base_path_point_end_z").as_double();
    this->declare_parameter<std::double_t>("start_track_path_point_id", 1);
    this->start_track_path_point_id=this->get_parameter("start_track_path_point_id").as_int();
    this->declare_parameter<std::double_t>("base_start_point_x", 0.004);
    this->base_start_point(0)=this->get_parameter("base_start_point_x").as_double();
    this->declare_parameter<std::double_t>("base_start_point_y", 1.0);
    this->base_start_point(1)=this->get_parameter("base_start_point_y").as_double();
    this->declare_parameter<std::double_t>("base_start_point_z", 0.004);
    this->base_start_point(2)=this->get_parameter("base_start_point_z").as_double();
    this->declare_parameter<std::double_t>("base_end_point_x", -0.004);
    this->base_end_point(0)=this->get_parameter("base_end_point_x").as_double();
    this->declare_parameter<std::double_t>("base_end_point_y", 1001.0);
    this->base_end_point(1)=this->get_parameter("base_end_point_y").as_double();
    this->declare_parameter<std::double_t>("base_end_point_z", -0.004);
    this->base_end_point(2)=this->get_parameter("base_end_point_z").as_double();
    this->declare_parameter<std::int64_t>("path_follow_nanotime_interval", this->path_follow_nanotime_interval);
    this->path_follow_nanotime_interval=this->get_parameter("path_follow_nanotime_interval").as_double();
    this->declare_parameter<std::double_t>("arc_path_alpha", this->arc_path_alpha);
    this->arc_path_alpha=this->get_parameter("arc_path_alpha").as_double();
    this->declare_parameter<std::double_t>("arc_path_theta", this->arc_path_theta);
    this->arc_path_theta=this->get_parameter("arc_path_theta").as_double();
    this->declare_parameter<std::double_t>("arc_path_radius", this->arc_path_radius);
    this->arc_path_radius=this->get_parameter("arc_path_radius").as_double();
    this->declare_parameter<std::double_t>("post_line_path_length", this->post_line_path_length);
    this->post_line_path_length=this->get_parameter("post_line_path_length").as_double();
    this->declare_parameter<std::double_t>("base_z_axis_x", 0.0);
    this->base_z_axis(0)=this->get_parameter("base_z_axis_x").as_double();
    this->declare_parameter<std::double_t>("base_z_axis_y", 0.0);
    this->base_z_axis(1)=this->get_parameter("base_z_axis_y").as_double();
    this->declare_parameter<std::double_t>("base_z_axis_z", 1.0);
    this->base_z_axis(2)=this->get_parameter("base_z_axis_z").as_double();
    this->declare_parameter<std::double_t>("base_y_axis_x", 0.0);
    this->base_y_axis(0)=this->get_parameter("base_y_axis_x").as_double();
    this->declare_parameter<std::double_t>("base_y_axis_y", 1.0);
    this->base_y_axis(1)=this->get_parameter("base_y_axis_y").as_double();
    this->declare_parameter<std::double_t>("base_y_axis_z", 0.0);
    this->base_y_axis(2)=this->get_parameter("base_y_axis_z").as_double();
    this->declare_parameter<std::double_t>("base_tolerance_deviation_factor", 0.08);
    double base_tolerance_deviation_factor = this->get_parameter("base_tolerance_deviation_factor").as_double();
    this->declare_parameter<std::double_t>("base_tolerance_angle_deviation", 10);
    this->base_tolerance_angle_deviation=this->get_parameter("base_tolerance_angle_deviation").as_double();  
    this->declare_parameter<std::double_t>("safe_path_length_factor", 10);
    this->safe_path_length_factor=this->get_parameter("safe_path_length_factor").as_double();
    this->declare_parameter<std::double_t>("bone_sample_interval", 1.0);
    this->bone_sample_interval=this->get_parameter("bone_sample_interval").as_double();

    if (joint_number == -1)
    {
        std::cout << "joint_number haven't initialized" <<std::endl;
        return;
    }
    for (int i=0;i<20;i++)
    {
        this->declare_parameter<std::double_t>(std::string("joint") + std::to_string(i)+std::string("_rigid1_length"), -1.0);
        this->declare_parameter<std::double_t>(std::string("joint") + std::to_string(i)+std::string("_rigid2_length"), -1.0);
        this->declare_parameter<std::double_t>(std::string("joint") + std::to_string(i)+std::string("_continuum_length"), -1.0);
    }
    this->transform_base_to_world = Eigen::Matrix4d::Identity();
    Eigen::Vector3d temp_x = this->base_y_axis.cross(this->base_z_axis);
    this->transform_base_to_world.block(0,0,3,3) << temp_x,this->base_y_axis,this->base_z_axis;
    this->transform_world_to_base = this->transform_base_to_world.inverse();
    for (int i=0;i<this->joint_number;i++)
    {  
        Joint temp_joint(this->get_parameter(std::string("joint")+std::to_string(i)+std::string("_rigid1_length")).as_double(),
                         this->get_parameter(std::string("joint")+std::to_string(i)+std::string("_rigid2_length")).as_double(),
                         this->get_parameter(std::string("joint")+std::to_string(i)+std::string("_continuum_length")).as_double());
        this->transform_joints_to_world[i] = this->transform_base_to_world;
        this->transform_world_to_joints[i] = this->transform_world_to_base;
        for (int j=0;j<i;j++)
        {
            this->transform_joints_to_world[i] = this->transform_joints_to_world[i]*this->joints[j].transform; 
            this->transform_world_to_joints[i] = this->joints[j].transform.inverse()*this->transform_joints_to_world[i];
        }
        this->joints.push_back(temp_joint);
        this->length+=temp_joint.length;
    };
    this->base_tolerance_deviation = this->joints[0].length*base_tolerance_deviation_factor;

    return;
}

void CDCR::path_follow_callback()
{
    // get base transform of base to world from the path point;
    getBasePose();
    if (this->flag_end_path_follow)
    {
        rclcpp::shutdown();
        return;
    }
    // start to fit the cdcr robot;
    fitCDCR();
    if (this->flag_end_path_follow)
    {
        rclcpp::shutdown();
        return;
    }
    return;
}

void CDCR::fitCDCR()
{
    int joint_id = 0;
    this->transform_joints_to_world[0] = this->transform_base_to_world;
    this->transform_world_to_joints[0] = this->transform_world_to_base.inverse();
    int closed_path_point_id = track_path_point_id;
    for (joint_id; joint_id<joint_number; joint_id++)
    {
        int target_point_id = closed_path_point_id+ceil(this->joints[joint_id].length/this->sample_interval);
        Eigen::Vector3d target_position = path_points[target_point_id];
        Eigen::Vector3d target_tangent_vec = (path_points[target_point_id+1]-path_points[target_point_id-1]).normalized();
        
    }
    track_path_point_id++;
    return;
}

void CDCR::discretePath()
{
    if (flag_discretized)
        return;
    switch (this->experience_type)
    {
    // case 1 is using the combination of line and circle;
    case 1:
    {
        int base_path_point_size = (int)ceil((base_path_point_end-base_path_point_start).norm()/this->sample_interval);
        for (int i=0;i<=base_path_point_size;i++)
        {
            Eigen::Vector3d temp_path_point = (double)(base_path_point_size-i)/(double)base_path_point_size*base_path_point_start
                                                +(double)i/(double)base_path_point_size*base_path_point_end;
            path_points.push_back(temp_path_point);
        }
        int arc_path_point_size = (int)ceil(arc_path_theta/180.0*M_PI * this->arc_path_radius/this->sample_interval);
        Eigen::Matrix4d transform_arc_path = Eigen::Matrix4d::Identity();
        transform_arc_path.block(0,3,3,1) = path_points.back();
        for (int i=1;i<=arc_path_point_size;i++)
        {
            double temp_theta = (double)i/(double)arc_path_point_size * arc_path_theta/180.0*M_PI;
            double temp_alpha = arc_path_alpha/180.0*M_PI;
            Eigen::Vector3d temp_arc_path_point(sin(temp_alpha)*(1-cos(temp_theta))*arc_path_radius,
                                                sin(temp_theta)*arc_path_radius,
                                                cos(temp_alpha)*(1-cos(temp_theta))*arc_path_radius);
            temp_arc_path_point = transform_arc_path*temp_arc_path_point;
            path_points.push_back(temp_arc_path_point);
        }
        double rad_theta = arc_path_theta/180.0*M_PI;
        double rad_alpha = arc_path_alpha/180.0*M_PI;
        Eigen::Vector3d vector_arc_end(sin(rad_theta)*sin(rad_alpha),
                                        cos(rad_theta),
                                        sin(rad_theta) * cos(rad_alpha));
        for (double i=1; i<=this->post_line_path_length+1e-4;i+=1.0)
        {
            path_points.push_back(path_points.back() + vector_arc_end);
        }
        break;
    }
    // default is using the B-spline;
    default:
    {
        break;        
    }
    }
    flag_discretized=true;
    return;
}

void CDCR::getCorrectTravelPointID()
{
    Eigen::Vector3d path_tangent_vec;
    double path_deviation;
    for (int i=1;i<path_points.size()-1;i++)
    {
        if (i=path_points.size()-2)
        {
            RCLCPP_ERROR(this->get_logger(), "UNKNOWN ERROR!, 173");
            this->flag_end_path_follow=true;
            return;
        }
        if (!baseDeviationCorrectCheck(i) || !baseDirectCorrectCheck(i))
            continue;
        correct_start_path_point_id = i;
        for (int j=i;j<path_points.size()-1;j++)
        {
            if (j=path_points.size()-2)
            {
                RCLCPP_ERROR(this->get_logger(), "UNKNOWN ERROR!, 204");
                this->flag_end_path_follow=true;
                return;
            }
            if (!baseDirectCorrectCheck(j)
                || !baseDeviationCorrectCheck(j)
                || !remainPathLengthCheck(j))
            {
                correct_end_path_point_id = j;
                break;
            }
        }
        RCLCPP_INFO(this->get_logger(),"the start track path point id should be the range (%d, %d)",correct_start_path_point_id,correct_end_path_point_id);
        if (this->start_track_path_point_id < correct_start_path_point_id || 
            this->start_track_path_point_id > correct_end_path_point_id)
        {
            RCLCPP_ERROR(this->get_logger(), "Track Path Error, track point wasn't in the travel range!!!");
            this->flag_end_path_follow = true;
        }
        return;
    }
}

void CDCR::path_follow()
{
    // discrete the path
    discretePath();
    if (flag_end_path_follow)
    {
        rclcpp::shutdown();
        return;
    }
    getCorrectTravelPointID();
    if (flag_end_path_follow)
    {
        rclcpp::shutdown();
        return;
    }
    this->track_path_point_id = this->start_track_path_point_id;
    this->timer = this->create_wall_timer(std::chrono::nanoseconds(path_follow_nanotime_interval),
                                        std::bind(&CDCR::path_follow_callback,this));
    return;
}

void CDCR::getBasePose()
{
    if (!baseDirectCorrectCheck(this->track_path_point_id))
    {
        this->flag_end_path_follow = true;
        RCLCPP_ERROR(this->get_logger(), "Base Track Direct ERROR !!!");
        return;   
    }
    if (!baseDeviationCorrectCheck(this->track_path_point_id))
    {
        this->flag_end_path_follow = true;
        RCLCPP_ERROR(this->get_logger(), "Base Track Deviation ERROR !!!");
        return;  
    }
    if(!remainPathLengthCheck(this->track_path_point_id))
    {
        this->flag_end_path_follow = true;
        RCLCPP_ERROR(this->get_logger(), "Remain path length is not sufficient !!!");
        return;
    }
    Eigen::Vector3d base_track_travel_point = getMediaInterPoint(path_points[this->track_path_point_id], this->base_end_point, this->base_start_point);
    this->transform_base_to_world.block(0,3,3,1) = base_track_travel_point;
    this->transform_world_to_base = this->transform_base_to_world.inverse();
    return;
}

Eigen::Vector3d CDCR::getMediaInterPoint(const Eigen::Vector3d& inter_point,const Eigen::Vector3d& line_end1,const Eigen::Vector3d& line_end2)
{
    double temp_proj_value=calVecProjValue(inter_point, line_end1,line_end2);
    double temp_norm_value = (line_end1-line_end2).norm();
    return (temp_proj_value/temp_norm_value * line_end2 + (temp_norm_value-temp_proj_value)/temp_norm_value*line_end1);
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
void CDCR::getPathDeviationAndNextIndex(const int& path_point_index_start, 
                                        const int& cdcr_point_index, 
                                        int& path_point_index_next_start)
{
    int temp_index = path_point_index_start;
    Eigen::Vector3d direction = this->cdcr_points.col(cdcr_point_index)-this->path_points[temp_index];
    std::cout << "here may cause error of eigen vector" << std::endl;
    double direction_value = this->cdcr_point_tangent_vectors.col(cdcr_point_index).dot(direction);
    if (direction_value < 0)
    {
        temp_index -= 1;
        for (int i=temp_index; i>=0; i--)
        {
            Eigen::Vector3d last_direction = direction;
            double last_direction_value = direction_value;
            direction=this->cdcr_points.col(cdcr_point_index)-this->path_points[i];
            direction_value = this->cdcr_point_tangent_vectors.col(cdcr_point_index).dot(direction);
            if (direction_value > 0)
            {
                double temp_sum = direction_value + std::abs(last_direction_value);
                Eigen::Vector3d interpolated_point = (temp_sum-direction_value)/temp_sum * this->path_points[i]
                                                    +(direction_value/temp_sum) * path_points[i+1];
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
            direction=this->cdcr_points.col(cdcr_point_index)-this->path_points[i];
            direction_value = this->cdcr_point_tangent_vectors.col(cdcr_point_index).dot(direction);
            if (direction_value < 0)
            {
                double temp_sum = last_direction_value + std::abs(direction_value);
                Eigen::Vector3d interpolated_point = (temp_sum-last_direction_value)/temp_sum * this->path_points[i-1]
                                                    +(last_direction_value/temp_sum) * path_points[i];
                this->cdcr_point_deviation_values[cdcr_point_index] = (interpolated_point-cdcr_points.col(cdcr_point_index)).norm();
                path_point_index_next_start = i;
                return;
            }
        }
    }
    return;
}

bool CDCR::baseDeviationCorrectCheck(const int& path_point_id)
{
    double path_deviation = (this->path_points[path_point_id].cross((this->base_start_point-this->base_end_point).normalized())).norm();
    double tempDotValue_1 = calVecProjValue(this->path_points[path_point_id], this->base_start_point, this->base_end_point);
    double tempDotValue_2 = calVecProjValue(this->path_points[path_point_id], this->base_end_point, this->base_start_point);
    if (tempDotValue_1 < 0 || tempDotValue_2 < 0 || path_deviation > this->base_tolerance_deviation) 
    {
        return false;
    }
    return true;
}

double CDCR::calVecProjValue(const Eigen::Vector3d& first_point, const Eigen::Vector3d& media_point, const Eigen::Vector3d& second_point)
{
    return (first_point-media_point).dot((second_point-media_point).normalized());
}

bool CDCR::baseDirectCorrectCheck(const int& path_point_id)
{
    Eigen::Vector3d path_tangent_vec = (path_points[path_point_id+1]-path_points[path_point_id-1]).normalized();
    if (acos(path_tangent_vec.dot(base_y_axis))/M_PI*180 > this->base_tolerance_angle_deviation)
        return false;
    return true;
}

bool CDCR::remainPathLengthCheck(const int& path_point_id)
{
    if (this->length*this->safe_path_length_factor > (path_points.size()-path_point_id)*sample_interval)
        return false;
    return true;
}