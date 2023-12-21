#include "cdcr.hpp"


CDCR::CDCR():Node("path_follow")
{
    this->weight_direction=10;
    this->weight_position=1;
    this->flag_end_path_follow = false;
    this->flag_discretized = false;
    this->flag_end_experience = false;
    // per_radius_fit_time_ofs.open("/home/weiwei/Desktop/project/path_follow/src/path_follow/data/per_radius_fit_time");
    // per_radius_max_deviation_ofs.open("/home/weiwei/Desktop/project/path_follow/src/path_follow/data/per_radius_max_deviation");
    // per_fitperiod_max_deviation_ofs.open("/home/weiwei/Desktop/project/path_follow/src/path_follow/data/per_fitperiod_max_deviation");
    // per_fitperiod_theta_value_ofs.open("/home/weiwei/Desktop/project/path_follow/src/path_follow/data/per_fitperiod_theta_value");
    // per_fitperiod_alpha_value_ofs.open("/home/weiwei/Desktop/project/path_follow/src/path_follow/data/per_fitperiod_alpha_value");

    this->declare_parameter<std::int16_t>("visualization_flag", 1);
    this->visualization_flag = this->get_parameter("visualization_flag").as_int();

    this->declare_parameter<std::double_t>("arc_path_radius_step", 4.0);
    this->arc_path_radius_step = this->get_parameter("arc_path_radius_step").as_double();

    this->declare_parameter<std::double_t>("alpha_lower_bound", -180.0);
    this->alpha_lower_bound = this->get_parameter("alpha_lower_bound").as_double()/180.0 * M_PI;
    this->declare_parameter<std::double_t>("alpha_upper_bound", 180.0);
    this->alpha_upper_bound = this->get_parameter("alpha_upper_bound").as_double()/180.0 * M_PI;
    this->declare_parameter<std::double_t>("theta_lower_bound", -90.0);
    this->theta_lower_bound = this->get_parameter("theta_lower_bound").as_double()/180.0 * M_PI;
    this->declare_parameter<std::double_t>("theta_upper_bound", 90.0);
    this->theta_upper_bound = this->get_parameter("theta_upper_bound").as_double()/180.0 * M_PI;
    this->declare_parameter<std::int64_t>("sleep_nano_time", 10000000);
    this->sleep_nano_time = this->get_parameter("sleep_nano_time").as_int();   
    this->declare_parameter<std::double_t>("deviation_marker_zoom_factor", 10.0);
    this->deviation_marker_zoom_factor = this->get_parameter("deviation_marker_zoom_factor").as_double();
    this->declare_parameter<std::double_t>("path_point_scale", 1.0);
    this->path_point_scale = this->get_parameter("path_point_scale").as_double();
    this->declare_parameter<std::double_t>("path_point_color_r", 1.0);
    this->path_point_color_r = this->get_parameter("path_point_color_r").as_double();
    this->declare_parameter<std::double_t>("path_point_color_g", 0.0);
    this->path_point_color_g = this->get_parameter("path_point_color_g").as_double();
    this->declare_parameter<std::double_t>("path_point_color_b", 0.0);
    this->path_point_color_b = this->get_parameter("path_point_color_b").as_double();
    this->declare_parameter<std::double_t>("path_point_color_a", 1.0);
    this->path_point_color_a = this->get_parameter("path_point_color_a").as_double();
    
    this->declare_parameter<std::double_t>("deviation_marker_scale_x", 4.0);
    this->deviation_marker_scale_x = this->get_parameter("deviation_marker_scale_x").as_double();
    this->declare_parameter<std::double_t>("deviation_marker_scale_y", 8.0);
    this->deviation_marker_scale_y = this->get_parameter("deviation_marker_scale_y").as_double();
    this->declare_parameter<std::double_t>("deviation_marker_scale_z", 8.0);
    this->deviation_marker_scale_z = this->get_parameter("deviation_marker_scale_z").as_double();
    this->declare_parameter<std::double_t>("sample_interval", 1.0);
    this->sample_interval = this->get_parameter("sample_interval").as_double();
    this->declare_parameter<std::int16_t>("joint_number", 20);
    this->joint_number = this->get_parameter("joint_number").as_int();
    this->declare_parameter<std::int16_t>("experience_type",1);
    this->experience_type=this->get_parameter("experience_type").as_int();

    this->declare_parameter<std::double_t>("base_path_point_start_x", 0.0);
    this->base_path_point_start(0)=this->get_parameter("base_path_point_start_x").as_double();
    this->declare_parameter<std::double_t>("base_path_point_start_y", 0.0);
    this->base_path_point_start(1)=this->get_parameter("base_path_point_start_y").as_double();
    this->declare_parameter<std::double_t>("base_path_point_start_z", 0.0);
    this->base_path_point_start(2)=this->get_parameter("base_path_point_start_z").as_double();

    this->declare_parameter<std::double_t>("base_path_point_end_x", 0.0);
    this->base_path_point_end(0)=this->get_parameter("base_path_point_end_x").as_double();
    this->declare_parameter<std::double_t>("base_path_point_end_y", 2100.0);
    this->base_path_point_end(1)=this->get_parameter("base_path_point_end_y").as_double();
    this->declare_parameter<std::double_t>("base_path_point_end_z", 0.0);
    this->base_path_point_end(2)=this->get_parameter("base_path_point_end_z").as_double();

    this->declare_parameter<std::int64_t>("start_track_path_point_id", 1);
    this->start_track_path_point_id=this->get_parameter("start_track_path_point_id").as_int();
    this->declare_parameter<std::double_t>("base_start_point_x", 0.0);
    this->base_start_point(0)=this->get_parameter("base_start_point_x").as_double();
    this->declare_parameter<std::double_t>("base_start_point_y", 1.0);
    this->base_start_point(1)=this->get_parameter("base_start_point_y").as_double();
    this->declare_parameter<std::double_t>("base_start_point_z", 0.0);
    this->base_start_point(2)=this->get_parameter("base_start_point_z").as_double();
    this->declare_parameter<std::double_t>("base_end_point_x", 0.0);
    this->base_end_point(0)=this->get_parameter("base_end_point_x").as_double();
    this->declare_parameter<std::double_t>("base_end_point_y", 2099.0);
    this->base_end_point(1)=this->get_parameter("base_end_point_y").as_double();
    this->declare_parameter<std::double_t>("base_end_point_z", 0.0);
    this->base_end_point(2)=this->get_parameter("base_end_point_z").as_double();
    this->declare_parameter<std::int64_t>("path_follow_nanotime_interval", this->path_follow_nanotime_interval);
    this->path_follow_nanotime_interval=this->get_parameter("path_follow_nanotime_interval").as_int();
    this->declare_parameter<std::double_t>("arc_path_alpha", 0.0);
    this->arc_path_alpha=this->get_parameter("arc_path_alpha").as_double();
    this->declare_parameter<std::double_t>("arc_path_theta", 180.0);
    this->arc_path_theta=this->get_parameter("arc_path_theta").as_double();
    this->declare_parameter<std::double_t>("min_arc_radius", 60.0);
    this->min_arc_radius=this->get_parameter("min_arc_radius").as_double();
    this->declare_parameter<std::double_t>("max_arc_radius", 500.0);
    this->max_arc_radius=this->get_parameter("max_arc_radius").as_double();
    this->declare_parameter<std::double_t>("arc_path_radius", 60.0);
    this->arc_path_radius=this->get_parameter("arc_path_radius").as_double();
    this->declare_parameter<std::double_t>("post_line_path_length", 2100.0);
    this->post_line_path_length=this->get_parameter("post_line_path_length").as_double();
    this->declare_parameter<std::double_t>("base_z_axis_x", 0.0);
    this->base_z_axis(0)=this->get_parameter("base_z_axis_x").as_double();
    this->declare_parameter<std::double_t>("base_z_axis_y", 1.0);
    this->base_z_axis(1)=this->get_parameter("base_z_axis_y").as_double();
    this->declare_parameter<std::double_t>("base_z_axis_z", 0.0);
    this->base_z_axis(2)=this->get_parameter("base_z_axis_z").as_double();
    this->declare_parameter<std::double_t>("base_y_axis_x", 1.0);
    this->base_y_axis(0)=this->get_parameter("base_y_axis_x").as_double();
    this->declare_parameter<std::double_t>("base_y_axis_y", 0.0);
    this->base_y_axis(1)=this->get_parameter("base_y_axis_y").as_double();
    this->declare_parameter<std::double_t>("base_y_axis_z", 0.0);
    this->base_y_axis(2)=this->get_parameter("base_y_axis_z").as_double();
    this->declare_parameter<std::double_t>("base_tolerance_deviation", 1);
    double base_tolerance_deviation = this->get_parameter("base_tolerance_deviation").as_double();
    this->declare_parameter<std::double_t>("base_tolerance_angle_deviation", 10);
    this->base_tolerance_angle_deviation=this->get_parameter("base_tolerance_angle_deviation").as_double();  
    this->declare_parameter<std::double_t>("safe_path_length_redundance", 80);
    this->safe_path_length_redundance=this->get_parameter("safe_path_length_redundance").as_double();
    this->declare_parameter<std::double_t>("bone_sample_interval", 1.0);
    this->bone_sample_interval=this->get_parameter("bone_sample_interval").as_double();
    this->declare_parameter<std::double_t>("weight_direction", 50.0);
    this->weight_direction=this->get_parameter("weight_direction").as_double();
    this->declare_parameter<std::double_t>("weight_position", 1.0);
    this->weight_position=this->get_parameter("weight_position").as_double();
    this->declare_parameter<std::double_t>("base_box_size_x", 100.0);
    this->base_box_size_x=this->get_parameter("base_box_size_x").as_double();
    this->declare_parameter<std::double_t>("base_box_size_y", 100.0);
    this->base_box_size_y=this->get_parameter("base_box_size_y").as_double();
    this->declare_parameter<std::double_t>("base_box_size_z", 300.0);
    this->base_box_size_z=this->get_parameter("base_box_size_z").as_double();   
    this->declare_parameter<std::float_t>("base_box_color_r", 0.1);
    this->base_box_color_r=this->get_parameter("base_box_color_r").as_double();   
    this->declare_parameter<std::float_t>("base_box_color_g", 0.05);
    this->base_box_color_g=this->get_parameter("base_box_color_g").as_double();   
    this->declare_parameter<std::float_t>("base_box_color_b", 0.05);
    this->base_box_color_b=this->get_parameter("base_box_color_b").as_double();   
    this->declare_parameter<std::float_t>("base_box_color_a", 1.0);
    this->base_box_color_a=this->get_parameter("base_box_color_a").as_double();  
    this->declare_parameter<std::double_t>("cdcr_point_size_x", 8.0);
    this->cdcr_point_size_x = this->get_parameter("cdcr_point_size_x").as_double();
    this->declare_parameter<std::double_t>("cdcr_point_size_y", 8.0);
    this->cdcr_point_size_y = this->get_parameter("cdcr_point_size_y").as_double();
    this->declare_parameter<std::double_t>("cdcr_point_size_z", 8.0);
    this->cdcr_point_size_z = this->get_parameter("cdcr_point_size_z").as_double();
    this->declare_parameter<std::float_t>("cdcr_point_color_r", 0.0);
    this->cdcr_point_color_r = this->get_parameter("cdcr_point_color_r").as_double();
    this->declare_parameter<std::float_t>("cdcr_point_color_g", 0.0);
    this->cdcr_point_color_g = this->get_parameter("cdcr_point_color_g").as_double();
    this->declare_parameter<std::float_t>("cdcr_point_color_b", 1.0);
    this->cdcr_point_color_b = this->get_parameter("cdcr_point_color_b").as_double();
    this->declare_parameter<std::float_t>("cdcr_point_color_a", 1.0);
    this->cdcr_point_color_a = this->get_parameter("cdcr_point_color_a").as_double();

    this->declare_parameter<std::double_t>("cdcr_plat_size_x", 80.0);
    this->cdcr_plat_size_x = this->get_parameter("cdcr_plat_size_x").as_double();
    this->declare_parameter<std::double_t>("cdcr_plat_size_y", 80.0);
    this->cdcr_plat_size_y = this->get_parameter("cdcr_plat_size_y").as_double();
    this->declare_parameter<std::double_t>("cdcr_plat_size_z", 8.0);
    this->cdcr_plat_size_z = this->get_parameter("cdcr_plat_size_z").as_double();
    this->declare_parameter<std::double_t>("cdcr_plat_color_r", 0.9);
    this->cdcr_plat_color_r= this->get_parameter("cdcr_plat_color_r").as_double();
    this->declare_parameter<std::double_t>("cdcr_plat_color_g", 0.2);
    this->cdcr_plat_color_g = this->get_parameter("cdcr_plat_color_g").as_double();
    this->declare_parameter<std::double_t>("cdcr_plat_color_b", 0.0);
    this->cdcr_plat_color_b = this->get_parameter("cdcr_plat_color_b").as_double();
    this->declare_parameter<std::double_t>("cdcr_plat_color_a", 1.0);
    this->cdcr_plat_color_a = this->get_parameter("cdcr_plat_color_a").as_double();

    for (int i=0;i<20;i++)
    {
        this->declare_parameter<std::double_t>(std::string("joint") + std::to_string(i)+std::string("_rigid1_length"), 0.0);
        this->declare_parameter<std::double_t>(std::string("joint") + std::to_string(i)+std::string("_rigid2_length"), 0.0);
        this->declare_parameter<std::double_t>(std::string("joint") + std::to_string(i)+std::string("_continuum_length"), 100.0);
    }
    this->transform_base_to_world = Eigen::Matrix4d::Identity();
    Eigen::Vector3d temp_x = this->base_y_axis.cross(this->base_z_axis);
    this->transform_base_to_world.block(0,0,3,3) << temp_x,this->base_y_axis,this->base_z_axis;
    this->transform_world_to_base = this->transform_base_to_world.inverse();
    int cdcr_point_size =0;
    for (int i=0;i<this->joint_number;i++)
    {
        Joint temp_joint(this->get_parameter(std::string("joint")+std::to_string(i)+std::string("_rigid1_length")).as_double(),
                         this->get_parameter(std::string("joint")+std::to_string(i)+std::string("_rigid2_length")).as_double(),
                         this->get_parameter(std::string("joint")+std::to_string(i)+std::string("_continuum_length")).as_double());
        if (temp_joint.length_rigid1 < 1e-4)
            temp_joint.rigid1_sample_point_size = 0;
        else
            temp_joint.rigid1_sample_point_size = ceil(temp_joint.length_rigid1/this->bone_sample_interval);
        if (temp_joint.length_rigid2 < 1e-4)
            temp_joint.rigid2_sample_point_size = 0;
        else
            temp_joint.rigid2_sample_point_size = ceil(temp_joint.length_rigid2/this->bone_sample_interval);
        temp_joint.continuum_sample_point_size = ceil(temp_joint.length_continuum/this->bone_sample_interval);
        temp_joint.sample_point_size = temp_joint.continuum_sample_point_size+temp_joint.rigid1_sample_point_size+temp_joint.rigid2_sample_point_size;
        cdcr_point_size += temp_joint.sample_point_size;

        this->transform_joints_to_world.push_back(this->transform_base_to_world);
        this->transform_world_to_joints.push_back(this->transform_world_to_base);
        for (int j=0;j<i;j++)
        {
            this->transform_joints_to_world[i] = this->transform_joints_to_world[i]*this->joints[j].transform;
            this->transform_world_to_joints[i] = this->joints[j].transform.inverse()*this->transform_world_to_joints[i];
        }
        this->joints.push_back(temp_joint);
        this->length+=temp_joint.length;
    };
    this->transform_joints_to_world.push_back(this->transform_joints_to_world[joint_number-1]*this->joints[joint_number-1].transform);
    this->transform_world_to_joints.push_back(this->joints[joint_number-1].transform.inverse()*this->transform_world_to_joints[joint_number-1]);

    this->base_visualization_pub=this->create_publisher<visualization_msgs::msg::Marker>("base_visualization",1);
    this->cdcr_plat_visualization_pub=this->create_publisher<visualization_msgs::msg::MarkerArray>("cdcr_plat_visualization",1);
    this->cdcr_point_visualization_pub=this->create_publisher<visualization_msgs::msg::Marker>("cdcr_point_visualization",1);
    this->deviation_marker_pub = this->create_publisher<visualization_msgs::msg::MarkerArray>("deviation_markers", 1);
    this->path_point_markers_pub = this->create_publisher<visualization_marker>("path_point_markers", 1);
    this->max_deviation_pub = this->create_publisher<std_msgs::msg::Float64>("max_deviation", 3);
    this->fit_time_pub = this->create_publisher<std_msgs::msg::Float64>("fit_time", 3);
    std::cout << "init finished !!!" << std::endl;
    return;
}


void CDCR::discretePath()
{
    path_points.resize(0);
    switch (this->experience_type)
    {
    // case 1 is using the combination of line and circle;
    case 1:
    {

        int base_path_point_size = ceil((base_path_point_end-base_path_point_start).norm()/this->sample_interval);
        std::cout << "base_path_point_size: "<< base_path_point_size << std::endl;
        for (int i=0;i<=base_path_point_size;i++)
        {
            Eigen::Vector3d temp_path_point = (double)(base_path_point_size-i)/(double)base_path_point_size*base_path_point_start
                                                +(double)i/(double)base_path_point_size*base_path_point_end;
            path_points.push_back(temp_path_point);
        }
        std::cout << "base_path_points.size(): " << path_points.size() << std::endl;
        double rad_theta = arc_path_theta/180.0*M_PI;
        double rad_alpha = arc_path_alpha/180.0*M_PI;
        int arc_path_point_size = ceil(std::abs(rad_theta) * this->arc_path_radius/this->sample_interval);
        std::cout << "arc_path_point_size(): " << arc_path_point_size << std::endl;
        for (int i=1;i<=arc_path_point_size;i++)
        {
            double temp_theta = (double)i/(double)arc_path_point_size * rad_theta;
            double temp_alpha = rad_alpha;
            Eigen::Vector3d temp_arc_path_point(sin(temp_alpha)*(1-cos(temp_theta))*arc_path_radius,
                                                sin(temp_theta)*arc_path_radius,
                                                cos(temp_alpha)*(1-cos(temp_theta))*arc_path_radius);
            temp_arc_path_point = temp_arc_path_point+this->base_path_point_end;
            path_points.push_back(temp_arc_path_point);
        }
        Eigen::Vector3d vector_arc_end(sin(rad_theta)*sin(rad_alpha),
                                        cos(rad_theta),
                                        sin(rad_theta) * cos(rad_alpha));
        for (double i=1; i<=this->post_line_path_length+1e-4;i+=1.0)
        {
            path_points.push_back(path_points.back() + vector_arc_end);
        }
        std::cout << "path_points.size(): " << path_points.size() << std::endl;
        break;
    }
    // case 2 is using the constant curvature change rate path;
    case 2:
    {
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


void CDCR::path_follow_exeperience()
{
    std::vector<double> experience_deviations;
    std::vector<double> experience_arc_radiuses;
    std::vector<double> time_spend;
    if (experience_type == 1)
    {
        for (this->arc_path_radius=this->min_arc_radius;this->arc_path_radius<=this->max_arc_radius+1e-4; this->arc_path_radius+=this->arc_path_radius_step)
        {
            // discrete the path
            discretePath();
            getCorrectTravelPointID();
            if (flag_end_experience)
            {
                rclcpp::shutdown();
                return;
            }
            double follow_max_deviation = 0.0;
            double temp_time_spend = 0.0;
            path_follow(temp_time_spend, follow_max_deviation);
            time_spend.push_back(temp_time_spend);
            experience_arc_radiuses.push_back(this->arc_path_radius);
            experience_deviations.push_back(follow_max_deviation);
            for (int i=0;i<joints.size();i++)
            {
                joints[i].theta = 1e-4;
                joints[i].alpha = 1e-3;
            }
        }
        // // TODO:
        // saveData();
    }
    else
    {
        // discrete the path
        discretePath();

        getCorrectTravelPointID();
        if (flag_end_experience)
        {
            rclcpp::shutdown();
            return;
        }
        double follow_max_deviation = 0.0;
        double temp_time_spend = 0.0;
        path_follow(temp_time_spend, follow_max_deviation);
        time_spend.push_back(temp_time_spend);
        experience_deviations.push_back(follow_max_deviation);
    }
    return;
}

void CDCR::visualPathMarkers()
{
    visualization_marker path;
    path.points.resize(0);
    path.type = visualization_marker::SPHERE_LIST;
    path.header.stamp = this->now();
    path.header.frame_id = "world";
    path.action = visualization_marker::ADD;
    path.color.r = path_point_color_r;
    path.color.b = path_point_color_b;
    path.color.g = path_point_color_g;
    path.color.a = path_point_color_a;
    path.scale.x = path_point_scale;
    path.scale.y = path_point_scale;
    path.scale.z = path_point_scale;
    path.pose.position.x = 0.0;
    path.pose.position.y = 0.0;
    path.pose.position.z = 0.0;
    path.pose.orientation.x = 0.0;
    path.pose.orientation.y = 0.0;
    path.pose.orientation.z = 0.0;
    path.pose.orientation.w = 1.0;
    int path_points_size = path_points.size();
    std::cout << "path_points_size: " << path_points_size << std::endl;
    for (int i=0;i<path_points_size;i++)
    {
        geometry_msgs::msg::Point temp_path_point;
        temp_path_point.x = path_points[i].x();
        temp_path_point.y = path_points[i].y();
        temp_path_point.z = path_points[i].z();
        path.points.push_back(temp_path_point);
    }
    this->path_point_markers_pub->publish(path);
    return;
}

void CDCR::visualizationCDCR()
{
    return;
}

void CDCR::visualizationDeviations() 
{

    return;
}

void CDCR::getCorrectTravelPointID()
{
    Eigen::Vector3d path_tangent_vec;
    double path_deviation;

    for (int i=1;i<path_points.size()-1;i++)
    {
        if (i>=(path_points.size()-2))
        {
            RCLCPP_ERROR(this->get_logger(), "UNKNOWN ERROR!, 173");
            this->flag_end_experience=true;
            return;
        }
        if (!baseDeviationCorrectCheck(i) || !baseDirectCorrectCheck(i))
            continue;
        if (!remainPathLengthCheck(i))
        {
            this->flag_end_experience=true;
            return;
        }
        correct_start_path_point_id = i;

        for (int j=i;j<path_points.size()-1;j++)
        {
            if (j==(path_points.size()-2))
            {
                RCLCPP_ERROR(this->get_logger(), "UNKNOWN ERROR!, 204");
                this->flag_end_experience=true;
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
            this->flag_end_experience = true;
        }
        return;
    }
}

void CDCR::path_follow(double& time_spend, double& max_deviation)
{
    RCLCPP_INFO(this->get_logger(), "path_follow: ");
    int fit_times=0;
    std::vector<int> max_deviation_path_point_ids;
    std::vector<double> max_deviations;
    for (this->track_path_point_id=this->start_track_path_point_id;this->track_path_point_id < this->correct_end_path_point_id;this->track_path_point_id++)
    {
        // get base transform of base to world from the path point;
        getBasePose();
        // start to fit the cdcr robot;
        rclcpp::Time t_start = this->now();
        fitCDCR();
        rclcpp::Time t_end = this->now();
        double t_spend = t_end.seconds()-t_start.seconds();

        // //debug
        // RCLCPP_INFO(this->get_logger(), "fit_time: %f", t_spend);

        // // debug
        // std_msgs::msg::Float64 t_spend_msg;
        // t_spend_msg.data = t_spend;
        // this->fit_time_pub->publish(t_spend_msg);
        
        time_spend += t_spend;
        fit_times++;
        get_cdcr_sample_points();

        if (visualization_flag != 0)
        {
            rclcpp::Time visual_t_start = this->now();
            visualization();
            rclcpp::Time visual_t_end = this->now();
        }

        // //debug
        // double visual_spend = visual_t_end.seconds()-visual_t_start.seconds();
        // RCLCPP_INFO(this->get_logger(), "visual_time: %f", visual_spend);
        // rclcpp::sleep_for(std::chrono::nanoseconds(10000000000));

        double temp_max_deviation = 0.0;
        int temp_max_deviation_path_point_id = 0;
        cal_deviation_get_max_deviation_path_point_id(temp_max_deviation,temp_max_deviation_path_point_id);
        // it's better to show the max deviation vector at the corrorsponding point.

        //debug
        std_msgs::msg::Float64 max_deviation_msg;
        max_deviation_msg.data =temp_max_deviation;
        this->max_deviation_pub->publish(max_deviation_msg);
        
        max_deviations.push_back(temp_max_deviation);
        max_deviation_path_point_ids.push_back(temp_max_deviation_path_point_id);
    }
    if (this->experience_type == 1)
    {
        //debug
        if (arc_path_radius >= 66.0 && arc_path_radius <= 70.0)
        {
            show_max_deviations(max_deviations,max_deviation_path_point_ids); 
            //todo
            rclcpp::sleep_for(std::chrono::nanoseconds(10000000000));
        }
    }

    time_spend = time_spend/(double)fit_times;
    RCLCPP_INFO(this->get_logger(), "fit_times: %d" , fit_times);
    RCLCPP_INFO(this->get_logger(), "time_spend: %f" , time_spend);
    max_deviation = *(std::max_element(max_deviations.begin(),max_deviations.end()));
    if(this->experience_type == 2)
    {
        //TODO: 将max_deviations列表中的内容输出为Excel文件
    }
    RCLCPP_INFO(this->get_logger(), "max_deviation: %f", max_deviation);
    return;
}
void CDCR::show_max_deviations(const std::vector<double>& max_deviations, const std::vector<int>& max_deviation_path_point_ids)
{
    //debug
    RCLCPP_INFO (this->get_logger(), "show_max_deviations()");
    int max_deviations_size = max_deviations.size();
    Eigen::Vector3d x_axis = Eigen::Vector3d(1.0,0.0,0.0);
    visualization_msgs::msg::MarkerArray deviation_markers;
    for (int i=0;i<max_deviations_size;i++)
    {
        Eigen::Vector3d temp_vec = (this->path_points[max_deviation_path_point_ids[i]+1]
                                    -this->path_points[max_deviation_path_point_ids[i]-1]).normalized();
        Eigen::Vector3d direct_vec = temp_vec.cross(x_axis);
        Eigen::Vector3d temp_position = this->path_points[max_deviation_path_point_ids[i]];
        visualization_msgs::msg::Marker temp_marker;
        temp_marker.header.frame_id = "world";
        temp_marker.id = i;
        temp_marker.type = visualization_msgs::msg::Marker::ARROW;
        temp_marker.scale.x = this->deviation_marker_scale_x;
        temp_marker.scale.y = this->deviation_marker_scale_y;
        temp_marker.scale.z = this->deviation_marker_scale_z;
        temp_marker.action = visualization_msgs::msg::Marker::ADD;
        temp_marker.pose.position.x = temp_position.x();
        temp_marker.pose.position.y = temp_position.y();
        temp_marker.pose.position.z = temp_position.z();
        temp_marker.pose.orientation.x = 0.0;
        temp_marker.pose.orientation.y = 0.0;
        temp_marker.pose.orientation.z = 0.0;
        temp_marker.pose.orientation.w = 1.0;
        temp_marker.color.r = 0.5;
        temp_marker.color.b = 0;
        temp_marker.color.g = 1;
        temp_marker.color.a = 1;
        geometry_msgs::msg::Point temp_start_point,temp_end_point;
        temp_start_point.x = 0;
        temp_start_point.y = 0;
        temp_start_point.z = 0;

        temp_end_point.x = direct_vec.x() * max_deviations[i] * this->deviation_marker_zoom_factor;
        temp_end_point.y = direct_vec.y() * max_deviations[i] * this->deviation_marker_zoom_factor;
        temp_end_point.z = direct_vec.z() * max_deviations[i] * this->deviation_marker_zoom_factor;
        // //debug
        // temp_end_point.x = 100.0;
        // temp_end_point.y = 100.0;
        // temp_end_point.z = 100.0;
        
        temp_marker.points.push_back(temp_start_point);
        temp_marker.points.push_back(temp_end_point);
        deviation_markers.markers.push_back(temp_marker);
    }
    deviation_marker_pub->publish(deviation_markers);

    // //debug
    // rclcpp::Rate temp_timer(2);
    // temp_timer.sleep();

    RCLCPP_INFO (this->get_logger(), "show_max_deviations finished()");
    return;
}
void CDCR::get_cdcr_sample_points()
{
    this->cdcr_points.resize(0);
    this->cdcr_points.push_back(this->transform_base_to_world.block(0,3,3,1));
    this->cdcr_segment_point_id.resize(0);
    this->cdcr_segment_point_id.push_back(0);
    for (int i=0;i<joint_number;i++)
    {
        Eigen::Vector3d rigid1_end_point = transform_joints_to_world[i].block(0,3,3,1) + transform_joints_to_world[i].block(0,0,3,3)*Eigen::Vector3d(0,0,joints[i].length_rigid1);
        Eigen::Vector3d rigid1_start_point = transform_joints_to_world[i].block(0,3,3,1);
        Eigen::Vector3d temp_point;
        int rigid1_point_num = ceil(joints[i].length_rigid1/this->bone_sample_interval);
        for (int j=1;j<=rigid1_point_num;j++)
        {
            temp_point = get_inter_point(j,rigid1_point_num,rigid1_start_point,rigid1_end_point);
            cdcr_points.push_back(temp_point);
        }
        Eigen::Matrix4d temp_transform_continuum_world = transform_joints_to_world[i];
        temp_transform_continuum_world.block(0,3,3,1) = rigid1_end_point;
        int continuum_point_num = ceil(joints[i].length_continuum/this->bone_sample_interval);
        for (int j=1;j<=continuum_point_num;j++)
        {
            temp_point = (temp_transform_continuum_world*Eigen::Vector4d(this->joints[i].length_continuum/this->joints[i].theta*(1-cos((double)j/(double)continuum_point_num*this->joints[i].theta))*cos(this->joints[i].alpha),
                                                                        this->joints[i].length_continuum/this->joints[i].theta*(1-cos((double)j/(double)continuum_point_num*this->joints[i].theta))*sin(this->joints[i].alpha),
                                                                        this->joints[i].length_continuum/this->joints[i].theta*sin((double)j/(double)continuum_point_num*this->joints[i].theta),1)).block(0,0,3,1);
            this->cdcr_points.push_back(temp_point);
        }
        int rigid2_point_num = ceil(this->joints[i].length_rigid2/this->bone_sample_interval);
        Eigen::Vector3d rigid2_end_point = (this->transform_joints_to_world[i]*this->joints[i].transform.col(3)).block(0,0,3,1);
        Eigen::Vector3d rigid2_start_point = (temp_transform_continuum_world*Eigen::Vector4d(this->joints[i].length_continuum/this->joints[i].theta*(1-cos(this->joints[i].theta))*cos(this->joints[i].alpha),
                                                                                            this->joints[i].length_continuum/this->joints[i].theta*(1-cos(this->joints[i].theta))*sin(this->joints[i].alpha),
                                                                                            this->joints[i].length_continuum/this->joints[i].theta*sin(this->joints[i].theta),1)).block(0,0,3,1);
        for (int j=1;j<=rigid2_point_num;j++)
        {
            temp_point=get_inter_point(j,rigid2_point_num,rigid2_start_point,rigid2_end_point);
            this->cdcr_points.push_back(temp_point);
        }
        this->cdcr_segment_point_id.push_back(cdcr_points.size()-1);
    }
    return;
}
void CDCR::visualization()
{
    // visualize the base box;
    std_msgs::msg::Header temp_header;
    temp_header.frame_id = "world";
    temp_header.stamp = this->now();
    visualization_msgs::msg::Marker base_visual_msg;
    base_visual_msg.header = temp_header;
    base_visual_msg.type = visualization_msgs::msg::Marker::Type::CUBE;
    base_visual_msg.color.r = this->base_box_color_r;
    base_visual_msg.color.b = this->base_box_color_g;
    base_visual_msg.color.g = this->base_box_color_b;
    base_visual_msg.color.a = this->base_box_color_a;
    base_visual_msg.scale.x = base_box_size_x;
    base_visual_msg.scale.y = base_box_size_y;
    base_visual_msg.scale.z = base_box_size_z;
    Eigen::Vector3d base_box_center_position=cdcr_points[0] - this->transform_base_to_world.block(0,2,3,1)*base_box_size_z/2;
    base_visual_msg.pose.position.x = base_box_center_position.x();
    base_visual_msg.pose.position.y = base_box_center_position.y();
    base_visual_msg.pose.position.z = base_box_center_position.z();
    //
    Eigen::Matrix3d rotate_base_to_world(this->transform_base_to_world.block(0,0,3,3));
    Eigen::Quaterniond base_box_quaternion(rotate_base_to_world);
    //
    base_visual_msg.pose.orientation.x = base_box_quaternion.x();
    base_visual_msg.pose.orientation.y = base_box_quaternion.y();
    base_visual_msg.pose.orientation.z = base_box_quaternion.z();
    base_visual_msg.pose.orientation.w = base_box_quaternion.w();
    // visualize the every cdcr point;
    visualization_msgs::msg::Marker cdcr_points_visual_msg;
    cdcr_points_visual_msg.header = temp_header;
    cdcr_points_visual_msg.type = visualization_msgs::msg::Marker::SPHERE_LIST;
    cdcr_points_visual_msg.color.r = this->cdcr_point_color_r;
    cdcr_points_visual_msg.color.g = this->cdcr_point_color_g;
    cdcr_points_visual_msg.color.b = this->cdcr_point_color_b;
    cdcr_points_visual_msg.color.a = this->cdcr_point_color_a;
    cdcr_points_visual_msg.scale.x = this->cdcr_point_size_x;
    cdcr_points_visual_msg.scale.y = this->cdcr_point_size_y;
    cdcr_points_visual_msg.scale.z = this->cdcr_point_size_z;
    cdcr_points_visual_msg.pose.orientation.w = 1.0;
    cdcr_points_visual_msg.pose.orientation.x = 0.0;
    cdcr_points_visual_msg.pose.orientation.y = 0.0;
    cdcr_points_visual_msg.pose.orientation.z = 0.0;
    for (int i=0;i<this->cdcr_points.size();i+=2)
    {
        geometry_msgs::msg::Point temp_point;
        temp_point.x = this->cdcr_points[i].x();
        temp_point.y = this->cdcr_points[i].y();
        temp_point.z = this->cdcr_points[i].z();
        cdcr_points_visual_msg.points.push_back(temp_point);
    }
    // visualize the cdcr plat;
    visualization_msgs::msg::MarkerArray cdcr_plats_visual_msg;
    for (int i=1;i<this->cdcr_segment_point_id.size();i++)
    {

        visualization_msgs::msg::Marker cdcr_plat_model;
        cdcr_plat_model.id = i;
        cdcr_plat_model.header = temp_header;
        cdcr_plat_model.type =visualization_msgs::msg::Marker::CYLINDER;
        cdcr_plat_model.pose.position.x = this->cdcr_points[cdcr_segment_point_id[i]].x();
        cdcr_plat_model.pose.position.y = this->cdcr_points[cdcr_segment_point_id[i]].y();
        cdcr_plat_model.pose.position.z = this->cdcr_points[cdcr_segment_point_id[i]].z();
        cdcr_plat_model.color.r = this->cdcr_plat_color_r;
        cdcr_plat_model.color.g = this->cdcr_plat_color_g;
        cdcr_plat_model.color.b = this->cdcr_plat_color_b;
        cdcr_plat_model.color.a = this->cdcr_plat_color_a;
        cdcr_plat_model.scale.x = this->cdcr_plat_size_x;
        cdcr_plat_model.scale.y = this->cdcr_plat_size_y;
        cdcr_plat_model.scale.z = this->cdcr_plat_size_z;

        Eigen::Matrix3d tempR = this->transform_joints_to_world[i].block(0,0,3,3);
        Eigen::Quaterniond tempQ(tempR);
        cdcr_plat_model.pose.orientation.x = tempQ.x();
        cdcr_plat_model.pose.orientation.y = tempQ.y();
        cdcr_plat_model.pose.orientation.z = tempQ.z();
        cdcr_plat_model.pose.orientation.w = tempQ.w();
        cdcr_plats_visual_msg.markers.push_back(cdcr_plat_model); 
    }
    this->base_visualization_pub->publish(base_visual_msg);
    this->cdcr_plat_visualization_pub->publish(cdcr_plats_visual_msg);
    this->cdcr_point_visualization_pub->publish(cdcr_points_visual_msg);
    this->visualPathMarkers();
    //debug
    this->sleep_nano_time = this->get_parameter("sleep_nano_time").as_int();
    rclcpp::Rate sleep_time(std::chrono::nanoseconds(this->sleep_nano_time));
    sleep_time.sleep();

    return;
}

Eigen::Vector3d CDCR::get_inter_point(const int& ratio_id, const int& total_id, const Eigen::Vector3d& start_point, const Eigen::Vector3d& end_point)
{
    return start_point+(end_point-start_point)*(double)ratio_id/(double)total_id;
}
void CDCR::cal_deviation_get_max_deviation_path_point_id(double& max_deviation, int& max_deviation_path_point_id)
{
    int temp_last_cdcr_point_id = 0;
    int temp_current_cdcr_point_id = 1;
    int temp_last_success_cdcr_point_id, temp_current_success_cdcr_point_id;
    for (int i=this->track_path_point_id+1;i < this->fit_end_path_point_id;i++)
    {
        bool flag_continue = false;
        Eigen::Vector3d temp_path_tangent_vec = (this->path_points[i+1]-this->path_points[i-1]);    
        // the vector of temp_last_cdcr_point to path_point.
        Eigen::Vector3d temp_vec1 = path_points[i]-this->cdcr_points[temp_last_cdcr_point_id];
        // the vector of current_cdcr_point to path_point.
        Eigen::Vector3d temp_vec2 = this->cdcr_points[temp_current_cdcr_point_id]-path_points[i];
        
        double temp_dot_value1 = temp_vec1.dot(temp_path_tangent_vec);
        double temp_dot_value2 = temp_vec2.dot(temp_path_tangent_vec);
        if (temp_dot_value1*temp_dot_value2 < 0)
        {
            if (temp_dot_value1 < 0)
            {
                do{
                    temp_last_cdcr_point_id-=1;
                    temp_current_cdcr_point_id-=1;
                    if (temp_last_cdcr_point_id < 0)
                    {
                        temp_last_cdcr_point_id = temp_last_success_cdcr_point_id;
                        temp_current_cdcr_point_id = temp_current_success_cdcr_point_id;
                        flag_continue = true;
                        break;
                    }
                    temp_vec1 = this->path_points[i]-this->cdcr_points[temp_last_cdcr_point_id];
                    temp_vec2 = this->cdcr_points[temp_current_cdcr_point_id]-this->path_points[i];
                    temp_dot_value1 = temp_vec1.dot(temp_path_tangent_vec);
                    temp_dot_value2 = temp_vec2.dot(temp_path_tangent_vec);
                }while(temp_dot_value1*temp_dot_value2<0);
            }
            else
            { 
                do{
                    temp_last_cdcr_point_id+=1;
                    temp_current_cdcr_point_id+=1;
                    if (temp_current_cdcr_point_id >= this->cdcr_points.size())
                    {
                        temp_last_cdcr_point_id = temp_last_success_cdcr_point_id;
                        temp_current_cdcr_point_id = temp_current_success_cdcr_point_id;
                        flag_continue = true;
                        break;
                    }
                    temp_vec1 = this->path_points[i]-this->cdcr_points[temp_last_cdcr_point_id];
                    temp_vec2 = this->cdcr_points[temp_current_cdcr_point_id]-this->path_points[i];
                    temp_dot_value1 = temp_vec1.dot(temp_path_tangent_vec);
                    temp_dot_value2 = temp_vec2.dot(temp_path_tangent_vec);
                }while(temp_dot_value1*temp_dot_value2<0);
            }
        }
        if (flag_continue)
        {
            continue;
        }
        temp_last_success_cdcr_point_id=temp_last_cdcr_point_id;
        temp_current_success_cdcr_point_id=temp_current_cdcr_point_id;
        double temp_deviation = ((this->cdcr_points[temp_current_cdcr_point_id]+this->cdcr_points[temp_last_cdcr_point_id])/2
                                -this->path_points[i]).norm();
        if (temp_deviation>max_deviation)
        {
            max_deviation = temp_deviation;
            max_deviation_path_point_id = i;
        }
    }
    return;
}
void CDCR::fitCDCR()
{
    this->transform_joints_to_world[0] = this->transform_base_to_world;
    this->transform_world_to_joints[0] = this->transform_world_to_base;
    int segment_start_path_point_id = this->track_path_point_id;
    for (int joint_id=0; joint_id<joint_number; joint_id++)
    {
        int target_path_point_id = segment_start_path_point_id+ceil(this->joints[joint_id].length/this->sample_interval);
        Eigen::Vector4d target_position;
        target_position << path_points[target_path_point_id],1.0;
        
        Eigen::Vector3d target_tangent_vec=(path_points[target_path_point_id+1]-path_points[target_path_point_id-1]).normalized();
        // transform the target_postion and tangent_vec to the frame of joint[joint_id]
        target_position = transform_world_to_joints[joint_id]*target_position;
        target_tangent_vec = transform_world_to_joints[joint_id].block(0,0,3,3)*target_tangent_vec;
        ceres::Problem fit_problem;
        fit_problem.AddResidualBlock(
            new ceres::AutoDiffCostFunction<x_residual,3,1,1>(
                new x_residual(
                    weight_position,
                    joints[joint_id].length_continuum,
                    joints[joint_id].length_rigid2,
                    joints[joint_id].length_rigid1,
                    target_position.block(0,0,3,1)
                )
            ),
            NULL,
            &joints[joint_id].alpha,&joints[joint_id].theta
        );
        // fit_problem.AddResidualBlock(
        //     new ceres::AutoDiffCostFunction<x_residual,1,1,1>(
        //         new x_residual(
        //             weight_position,
        //             joints[joint_id].length_continuum,
        //             joints[joint_id].length_rigid2,
        //             target_position.x()
        //         )
        //     ),
        //     NULL,
        //     &joints[joint_id].alpha,&joints[joint_id].theta
        // );
        // fit_problem.AddResidualBlock(
        //     new ceres::AutoDiffCostFunction<y_residual,1,1,1>(
        //         new y_residual(
        //             weight_position,
        //             joints[joint_id].length_continuum,
        //             joints[joint_id].length_rigid2,
        //             target_position.y()
        //         )
        //     ),
        //     NULL,
        //     &joints[joint_id].alpha,&joints[joint_id].theta    
        // );
        // fit_problem.AddResidualBlock(
        //     new ceres::AutoDiffCostFunction<z_residual,1,1>(
        //         new z_residual(
        //             weight_position,
        //             joints[joint_id].length_continuum,
        //             joints[joint_id].length_rigid1,
        //             joints[joint_id].length_rigid2,
        //             target_position.z()
        //         )
        //     ),
        //     NULL,
        //     &joints[joint_id].theta
        // );

        fit_problem.AddResidualBlock(
            new ceres::AutoDiffCostFunction<angle_residual,1,1,1>(
                new angle_residual(
                    weight_direction,
                    joints[joint_id].length_rigid1,
                    joints[joint_id].length_continuum,
                    joints[joint_id].length_rigid2,
                    target_tangent_vec
                )
            ),
            NULL,
            &joints[joint_id].alpha,&joints[joint_id].theta
        );
        fit_problem.SetParameterLowerBound(&joints[joint_id].alpha, 0, this->alpha_lower_bound);
        fit_problem.SetParameterLowerBound(&joints[joint_id].theta, 0, this->theta_lower_bound);
        fit_problem.SetParameterUpperBound(&joints[joint_id].alpha, 0, this->alpha_upper_bound);
        fit_problem.SetParameterUpperBound(&joints[joint_id].theta, 0, this->theta_upper_bound);
        ceres::Solver::Options option;
        option.max_num_iterations=50;
        option.minimizer_progress_to_stdout = false;
        option.linear_solver_type=ceres::DENSE_QR;
        // option.trust_region_strategy_type=ceres::DOGLEG;
        option.logging_type=ceres::SILENT;
        ceres::Solver::Summary summary;
        ceres::Solve(option,&fit_problem,&summary);
        if (joints[joint_id].theta < 0)
        {
            joints[joint_id].theta = std::abs(joints[joint_id].theta);
            joints[joint_id].alpha = (joints[joint_id].alpha + M_PI) > M_PI ?  (joints[joint_id].alpha-M_PI) : (joints[joint_id].alpha+M_PI);
        }
        Eigen::Vector3d joint_end_position;
        transform_joints_to_world[joint_id+1] = transform_joints_to_world[joint_id] * joints[joint_id].getTransform();
        transform_world_to_joints[joint_id+1] = joints[joint_id].transform.inverse()*transform_world_to_joints[joint_id];            
        joint_end_position = transform_joints_to_world[joint_id+1].block(0,3,3,1);
        find_closed_path_point(target_path_point_id,joint_end_position,segment_start_path_point_id);
    }
    // //debug
    // if (track_path_point_id >= 1000)
    // {
    //     for (int i=0;i<joint_number;i++)
    //     {
    //         RCLCPP_INFO(this->get_logger(),"joint[%d].theta: %f", i, joints[i].theta);
    //         RCLCPP_INFO(this->get_logger(),"joint[%d].alpha: %f", i, joints[i].alpha);
    //     }
    //     rclcpp::Rate temp_timer(std::chrono::nanoseconds(300000000));
    //     if(!temp_timer.sleep())
    //     {
    //         RCLCPP_ERROR(this->get_logger(), "can't sleep");
    //         rclcpp::shutdown();
            
    //     } 
    // }
    this->fit_end_path_point_id =segment_start_path_point_id;
    return;
}

void CDCR::find_closed_path_point(const int& start_path_point_id,const Eigen::Vector3d& joint_end_position, int& segment_start_path_point_id)
{
    int temp_path_point_id = start_path_point_id;
    Eigen::Vector3d temp_path_tangent_vec=this->path_points[temp_path_point_id+1]-this->path_points[temp_path_point_id-1];
    Eigen::Vector3d temp_direction=joint_end_position-path_points[temp_path_point_id];
    double temp_dot_value = temp_path_tangent_vec.dot(temp_direction);
    if (temp_dot_value > 0)
    {   
        do
        {
            temp_path_point_id++;
            Eigen::Vector3d temp_path_tangent_vec=this->path_points[temp_path_point_id+1]-this->path_points[temp_path_point_id-1];
            Eigen::Vector3d temp_direction=joint_end_position-path_points[temp_path_point_id];
            temp_dot_value = temp_path_tangent_vec.dot(temp_direction);
        }while(temp_dot_value>0 && temp_path_point_id<path_points.size()-2);        
    }
    else 
    {
        do
        {
            temp_path_point_id--;
            Eigen::Vector3d temp_path_tangent_vec=this->path_points[temp_path_point_id+1]-this->path_points[temp_path_point_id-1];
            Eigen::Vector3d temp_direction=joint_end_position-path_points[temp_path_point_id];
            temp_dot_value = temp_path_tangent_vec.dot(temp_direction);
        }while(temp_dot_value<0 && temp_path_point_id>1);     
    }
    segment_start_path_point_id = temp_path_point_id;
    return;
}


void CDCR::getBasePose()
{
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
    if (acos(path_tangent_vec.dot(base_z_axis))/M_PI*180 > this->base_tolerance_angle_deviation)
        return false;
    return true;
}

bool CDCR::remainPathLengthCheck(const int& path_point_id)
{
    if (this->length + this->safe_path_length_redundance > (path_points.size()-path_point_id)*sample_interval)
        return false;
    return true;
}