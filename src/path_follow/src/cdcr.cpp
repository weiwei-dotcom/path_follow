#include "cdcr.hpp"


CDCR::CDCR():Node("path_follow")
{

    flag_first_fit = true;

    // this->flag_end_path_follow = false;
    // this->flag_discretized = false;
    this->flag_end_experience = false;
    // per_radius_fit_time_ofs.open("/home/weiwei/Desktop/project/path_follow/src/path_follow/data/per_radius_fit_time.xlsx");
    // per_radius_max_deviation_ofs.open("/home/weiwei/Desktop/project/path_follow/src/path_follow/data/per_radius_max_deviation.xlsx");
    // arc_radius_ofs.open("/home/weiwei/Desktop/project/path_follow/src/path_follow/data/arc_radius.xlsx");
    // per_fitperiod_max_deviation_ofs.open("/home/weiwei/Desktop/project/path_follow/src/path_follow/data/per_fitperiod_max_deviation.xlsx");
    // per_fitperiod_theta_value_ofs.open("/home/weiwei/Desktop/project/path_follow/src/path_follow/data/per_fitperiod_theta_value.xlsx");
    // per_fitperiod_alpha_value_ofs.open("/home/weiwei/Desktop/project/path_follow/src/path_follow/data/per_fitperiod_alpha_value.xlsx");
    
    this->declare_parameter<std::int16_t>("flag_visualize_b_spline_marker",1);
    this->flag_visualize_b_spline_marker = this->get_parameter("flag_visualize_b_spline_marker").as_int();
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
    this->declare_parameter<std::int64_t>("sleep_nano_time", 0);
    this->sleep_nano_time = this->get_parameter("sleep_nano_time").as_int();   
    this->declare_parameter<std::double_t>("deviation_marker_zoom_factor", 2.0);
    this->deviation_marker_zoom_factor = this->get_parameter("deviation_marker_zoom_factor").as_double();
    this->declare_parameter<std::double_t>("path_point_scale", 1.0);
    this->path_point_scale = this->get_parameter("path_point_scale").as_double();
    this->declare_parameter<std::double_t>("path_point_color_r", 0.1);
    this->path_point_color_r = this->get_parameter("path_point_color_r").as_double();
    this->declare_parameter<std::double_t>("path_point_color_g", 0.8);
    this->path_point_color_g = this->get_parameter("path_point_color_g").as_double();
    this->declare_parameter<std::double_t>("path_point_color_b", 0.2);
    this->path_point_color_b = this->get_parameter("path_point_color_b").as_double();
    this->declare_parameter<std::double_t>("path_point_color_a", 1.0);
    this->path_point_color_a = this->get_parameter("path_point_color_a").as_double();
    
    this->declare_parameter<std::double_t>("deviation_marker_scale_x", 1.0);
    this->deviation_marker_scale_x = this->get_parameter("deviation_marker_scale_x").as_double();
    this->declare_parameter<std::double_t>("deviation_marker_scale_y", 0.0);
    this->deviation_marker_scale_y = this->get_parameter("deviation_marker_scale_y").as_double();
    this->declare_parameter<std::double_t>("deviation_marker_scale_z", 0.0);
    this->deviation_marker_scale_z = this->get_parameter("deviation_marker_scale_z").as_double();
    this->declare_parameter<std::double_t>("sample_interval", 1.0);
    this->sample_interval = this->get_parameter("sample_interval").as_double();
    this->declare_parameter<std::int16_t>("joint_number", 8);
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

    this->declare_parameter<std::int64_t>("start_track_path_point_id", 500);
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
    this->declare_parameter<std::int64_t>("path_follow_nanotime_interval", 500000000);
    this->path_follow_nanotime_interval=this->get_parameter("path_follow_nanotime_interval").as_int();
    this->declare_parameter<std::double_t>("arc_path_alpha", 0.0);
    this->arc_path_alpha=this->get_parameter("arc_path_alpha").as_double();
    this->declare_parameter<std::double_t>("arc_path_theta", 180.0);
    this->arc_path_theta=this->get_parameter("arc_path_theta").as_double();
    this->declare_parameter<std::double_t>("min_arc_radius", 60.0);
    this->min_arc_radius=this->get_parameter("min_arc_radius").as_double();
    this->declare_parameter<std::double_t>("max_arc_radius", 240.0);
    this->max_arc_radius=this->get_parameter("max_arc_radius").as_double();

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
    this->declare_parameter<std::double_t>("base_tolerance_deviation", 1.0);
    double base_tolerance_deviation = this->get_parameter("base_tolerance_deviation").as_double();
    this->declare_parameter<std::double_t>("base_tolerance_angle_deviation", 2.0);
    this->base_tolerance_angle_deviation=this->get_parameter("base_tolerance_angle_deviation").as_double();  
    this->declare_parameter<std::double_t>("safe_path_length_redundance", 200.0);
    this->safe_path_length_redundance=this->get_parameter("safe_path_length_redundance").as_double();
    this->declare_parameter<std::double_t>("bone_sample_interval", 1.0);
    this->bone_sample_interval=this->get_parameter("bone_sample_interval").as_double();
    
    // this->declare_parameter<std::double_t>("weight_direction", 0.970588);
    this->declare_parameter<std::double_t>("weight_direction", 0.0);
    this->weight_direction=this->get_parameter("weight_direction").as_double();

    // this->declare_parameter<std::double_t>("weight_position", 0.029412);
    this->declare_parameter<std::double_t>("weight_position", 1.0);
    this->weight_position=this->get_parameter("weight_position").as_double();
    
    this->declare_parameter<std::double_t>("base_box_size_x", 100.0);
    this->base_box_size_x=this->get_parameter("base_box_size_x").as_double();
    this->declare_parameter<std::double_t>("base_box_size_y", 100.0);
    this->base_box_size_y=this->get_parameter("base_box_size_y").as_double();
    this->declare_parameter<std::double_t>("base_box_size_z", 280.0);
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
    this->declare_parameter<std::double_t>("cdcr_plat_color_g", 0.1);
    this->cdcr_plat_color_g = this->get_parameter("cdcr_plat_color_g").as_double();
    this->declare_parameter<std::double_t>("cdcr_plat_color_b", 0.4);
    this->cdcr_plat_color_b = this->get_parameter("cdcr_plat_color_b").as_double();
    this->declare_parameter<std::double_t>("cdcr_plat_color_a", 1.0);
    this->cdcr_plat_color_a = this->get_parameter("cdcr_plat_color_a").as_double();

    // declare and get the b-spline interval points, start_end_point_derivatives and time_interval_value;
    this->declare_parameter<std::int16_t>("number_ctrl_points", 12);
    number_ctrl_points=this->get_parameter("number_ctrl_points").as_int();
    this->ctrl_points = Eigen::MatrixXd(3, number_ctrl_points);

    Eigen::Vector3d temp_control_point1;
    this->declare_parameter<std::double_t>("bspline_control_point1_x", 0.0);
    double bspline_control_point1_x = this->get_parameter("bspline_control_point1_x").as_double();
    this->declare_parameter<std::double_t>("bspline_control_point1_y", 120.0);
    double bspline_control_point1_y = this->get_parameter("bspline_control_point1_y").as_double();
    this->declare_parameter<std::double_t>("bspline_control_point1_z", 0.0);
    double bspline_control_point1_z = this->get_parameter("bspline_control_point1_z").as_double();
    temp_control_point1 << bspline_control_point1_x, bspline_control_point1_y, bspline_control_point1_z;
    this->ctrl_points.col(1) = temp_control_point1;

    Eigen::Vector3d temp_control_point2;
    this->declare_parameter<std::double_t>("bspline_control_point2_x", 0.0);
    double bspline_control_point2_x = this->get_parameter("bspline_control_point2_x").as_double();
    this->declare_parameter<std::double_t>("bspline_control_point2_y", 135.0);
    double bspline_control_point2_y = this->get_parameter("bspline_control_point2_y").as_double();
    this->declare_parameter<std::double_t>("bspline_control_point2_z", 110.0);
    double bspline_control_point2_z = this->get_parameter("bspline_control_point2_z").as_double();
    temp_control_point2 << bspline_control_point2_x, bspline_control_point2_y, bspline_control_point2_z;
    this->ctrl_points.col(2) = temp_control_point2;
    
    Eigen::Vector3d temp_control_point3;
    this->declare_parameter<std::double_t>("bspline_control_point3_x", 27.0);
    double bspline_control_point3_x = this->get_parameter("bspline_control_point3_x").as_double();
    this->declare_parameter<std::double_t>("bspline_control_point3_y", 235.0);
    double bspline_control_point3_y = this->get_parameter("bspline_control_point3_y").as_double();
    this->declare_parameter<std::double_t>("bspline_control_point3_z", 185.0);
    double bspline_control_point3_z = this->get_parameter("bspline_control_point3_z").as_double();
    temp_control_point3 << bspline_control_point3_x, bspline_control_point3_y, bspline_control_point3_z;
    this->ctrl_points.col(3) = temp_control_point3;
    
    Eigen::Vector3d temp_control_point4;
    this->declare_parameter<std::double_t>("bspline_control_point4_x", 90.0);
    double bspline_control_point4_x = this->get_parameter("bspline_control_point4_x").as_double();
    this->declare_parameter<std::double_t>("bspline_control_point4_y", 355.0);
    double bspline_control_point4_y = this->get_parameter("bspline_control_point4_y").as_double();
    this->declare_parameter<std::double_t>("bspline_control_point4_z", 205.0);
    double bspline_control_point4_z = this->get_parameter("bspline_control_point4_z").as_double();
    temp_control_point4 << bspline_control_point4_x, bspline_control_point4_y, bspline_control_point4_z;
    this->ctrl_points.col(4) = temp_control_point4; 
    
    Eigen::Vector3d temp_control_point5;
    this->declare_parameter<std::double_t>("bspline_control_point5_x", 150.0);
    double bspline_control_point5_x = this->get_parameter("bspline_control_point5_x").as_double();
    this->declare_parameter<std::double_t>("bspline_control_point5_y", 500.0);
    double bspline_control_point5_y = this->get_parameter("bspline_control_point5_y").as_double();
    this->declare_parameter<std::double_t>("bspline_control_point5_z", 170.0);
    double bspline_control_point5_z = this->get_parameter("bspline_control_point5_z").as_double();
    temp_control_point5 << bspline_control_point5_x, bspline_control_point5_y, bspline_control_point5_z;
    this->ctrl_points.col(5) = temp_control_point5; 
    
    Eigen::Vector3d temp_control_point6;
    this->declare_parameter<std::double_t>("bspline_control_point6_x", 150.0);
    double bspline_control_point6_x = this->get_parameter("bspline_control_point6_x").as_double();
    this->declare_parameter<std::double_t>("bspline_control_point6_y", 630.0);
    double bspline_control_point6_y = this->get_parameter("bspline_control_point6_y").as_double();
    this->declare_parameter<std::double_t>("bspline_control_point6_z", 150.0);
    double bspline_control_point6_z = this->get_parameter("bspline_control_point6_z").as_double();
    temp_control_point6 << bspline_control_point6_x, bspline_control_point6_y, bspline_control_point6_z;
    this->ctrl_points.col(6) = temp_control_point6; 
   
    Eigen::Vector3d temp_control_point7;
    this->declare_parameter<std::double_t>("bspline_control_point7_x", 130.0);
    double bspline_control_point7_x = this->get_parameter("bspline_control_point7_x").as_double();
    this->declare_parameter<std::double_t>("bspline_control_point7_y", 770.0);
    double bspline_control_point7_y = this->get_parameter("bspline_control_point7_y").as_double();
    this->declare_parameter<std::double_t>("bspline_control_point7_z", 130.0);
    double bspline_control_point7_z = this->get_parameter("bspline_control_point7_z").as_double();
    temp_control_point7 << bspline_control_point7_x, bspline_control_point7_y, bspline_control_point7_z;
    this->ctrl_points.col(7) = temp_control_point7; 
    
    Eigen::Vector3d temp_control_point8;
    this->declare_parameter<std::double_t>("bspline_control_point8_x", 110.0);
    double bspline_control_point8_x = this->get_parameter("bspline_control_point8_x").as_double();
    this->declare_parameter<std::double_t>("bspline_control_point8_y", 940.0);
    double bspline_control_point8_y = this->get_parameter("bspline_control_point8_y").as_double();
    this->declare_parameter<std::double_t>("bspline_control_point8_z", 110.0);
    double bspline_control_point8_z = this->get_parameter("bspline_control_point8_z").as_double();
    temp_control_point8 << bspline_control_point8_x, bspline_control_point8_y, bspline_control_point8_z;
    this->ctrl_points.col(8) = temp_control_point8; 
    
    Eigen::Vector3d temp_interval_point10;
    this->declare_parameter<std::double_t>("bspline_interval_point10_x", 110.0);
    double bspline_interval_point10_x = this->get_parameter("bspline_interval_point10_x").as_double();
    this->declare_parameter<std::double_t>("bspline_interval_point10_y", 900.0);
    double bspline_interval_point10_y = this->get_parameter("bspline_interval_point10_y").as_double();
    this->declare_parameter<std::double_t>("bspline_interval_point10_z", 110.0);
    double bspline_interval_point10_z = this->get_parameter("bspline_interval_point10_z").as_double();
    temp_interval_point10 << bspline_interval_point10_x, bspline_interval_point10_y, bspline_interval_point10_z;
    this->temp_b_spline_path_interval_poins.push_back(temp_interval_point10); 
    
    Eigen::Vector3d temp_interval_point11;
    this->declare_parameter<std::double_t>("bspline_interval_point11_x", 100.0);
    double bspline_interval_point11_x = this->get_parameter("bspline_interval_point11_x").as_double();
    this->declare_parameter<std::double_t>("bspline_interval_point11_y", 1100.0);
    double bspline_interval_point11_y = this->get_parameter("bspline_interval_point11_y").as_double();
    this->declare_parameter<std::double_t>("bspline_interval_point11_z", 100.0);
    double bspline_interval_point11_z = this->get_parameter("bspline_interval_point11_z").as_double();
    temp_interval_point11 << bspline_interval_point11_x, bspline_interval_point11_y, bspline_interval_point11_z;
    this->temp_b_spline_path_interval_poins.push_back(temp_interval_point11);

    // declare and get start_end_point_derivatives and time_interval_value;
    Eigen::Vector3d temp_start_vel;
    this->declare_parameter<std::double_t>("bspline_start_vel_x", 0.0);
    temp_start_vel.x() = this->get_parameter("bspline_start_vel_x").as_double();
    this->declare_parameter<std::double_t>("bspline_start_vel_y", 4.0);
    temp_start_vel.y() = this->get_parameter("bspline_start_vel_y").as_double();
    this->declare_parameter<std::double_t>("bspline_start_vel_z", 0.0);
    temp_start_vel.z() = this->get_parameter("bspline_start_vel_z").as_double();
    this->b_spline_start_end_derivatives.push_back(temp_start_vel);
    
    Eigen::Vector3d temp_end_vel;
    this->declare_parameter<std::double_t>("bspline_end_vel_x", 0.0);
    temp_end_vel.x() = this->get_parameter("bspline_end_vel_x").as_double();
    this->declare_parameter<std::double_t>("bspline_end_vel_y", 3.0);
    temp_end_vel.y() = this->get_parameter("bspline_end_vel_y").as_double();
    this->declare_parameter<std::double_t>("bspline_end_vel_z", 0.0);
    temp_end_vel.z() = this->get_parameter("bspline_end_vel_z").as_double();
    this->b_spline_start_end_derivatives.push_back(temp_end_vel);
    
    Eigen::Vector3d temp_start_acc;
    this->declare_parameter<std::double_t>("bspline_start_acc_x", 0.0);
    temp_start_acc.x() = this->get_parameter("bspline_start_acc_x").as_double();
    this->declare_parameter<std::double_t>("bspline_start_acc_y", 0.0);
    temp_start_acc.y() = this->get_parameter("bspline_start_acc_y").as_double();
    this->declare_parameter<std::double_t>("bspline_start_acc_z", 0.0);
    temp_start_acc.z() = this->get_parameter("bspline_start_acc_z").as_double();
    this->b_spline_start_end_derivatives.push_back(temp_start_acc);
    
    Eigen::Vector3d temp_end_acc;
    this->declare_parameter<std::double_t>("bspline_end_acc_x", 0.0);
    temp_end_acc.x() = this->get_parameter("bspline_end_acc_x").as_double();
    this->declare_parameter<std::double_t>("bspline_end_acc_y", 0.0);
    temp_end_acc.y() = this->get_parameter("bspline_end_acc_y").as_double();
    this->declare_parameter<std::double_t>("bspline_end_acc_z", 0.0);
    temp_end_acc.z() = this->get_parameter("bspline_end_acc_z").as_double();
    this->b_spline_start_end_derivatives.push_back(temp_end_acc);

    this->declare_parameter<std::double_t>("time_interval", 30.0);
    this->time_interval = this->get_parameter("time_interval").as_double();

    //cylinder1 obstacle's config param
    this->declare_parameter<std::double_t> ("cylinder1_scale_x", 300.0);
    this->declare_parameter<std::double_t> ("cylinder1_scale_y", 300.0);
    this->declare_parameter<std::double_t> ("cylinder1_scale_z", 600.0);
    this->declare_parameter<std::double_t> ("cylinder1_color_r", 1.0);
    this->declare_parameter<std::double_t> ("cylinder1_color_g", 0.0);
    this->declare_parameter<std::double_t> ("cylinder1_color_b", 0.5);
    this->declare_parameter<std::double_t> ("cylinder1_position_x", 0.0);
    this->declare_parameter<std::double_t> ("cylinder1_position_y", 2430.0);
    this->declare_parameter<std::double_t> ("cylinder1_position_z", 5.0);
    this->declare_parameter<std::double_t> ("cylinder1_axis_x", -5.0);
    this->declare_parameter<std::double_t> ("cylinder1_axis_y", 4.0);
    this->declare_parameter<std::double_t> ("cylinder1_axis_z", 3.0);
    this->cylinder1_axis_x = this->get_parameter("cylinder1_axis_x").as_double();
    this->cylinder1_axis_y = this->get_parameter("cylinder1_axis_y").as_double();
    this->cylinder1_axis_z = this->get_parameter("cylinder1_axis_z").as_double();
    this->cylinder1_position_z = this->get_parameter("cylinder1_position_z").as_double();
    this->cylinder1_position_y = this->get_parameter("cylinder1_position_y").as_double();
    this->cylinder1_position_x = this->get_parameter("cylinder1_position_x").as_double();
    this->cylinder1_color_b = this->get_parameter("cylinder1_color_b").as_double();
    this->cylinder1_color_g = this->get_parameter("cylinder1_color_g").as_double();
    this->cylinder1_color_r = this->get_parameter("cylinder1_color_r").as_double();
    this->cylinder1_scale_z = this->get_parameter("cylinder1_scale_z").as_double();
    this->cylinder1_scale_y = this->get_parameter("cylinder1_scale_y").as_double();
    this->cylinder1_scale_x = this->get_parameter("cylinder1_scale_x").as_double();

    //cylinder2 obstacle's config param
    this->declare_parameter<std::double_t> ("cylinder2_scale_x", 300.0);
    this->declare_parameter<std::double_t> ("cylinder2_scale_y", 300.0);
    this->declare_parameter<std::double_t> ("cylinder2_scale_z", 600.0);
    this->declare_parameter<std::double_t> ("cylinder2_color_r", 1.0);
    this->declare_parameter<std::double_t> ("cylinder2_color_g", 0.0);
    this->declare_parameter<std::double_t> ("cylinder2_color_b", 0.5);
    this->declare_parameter<std::double_t> ("cylinder2_position_x", 0.0);
    this->declare_parameter<std::double_t> ("cylinder2_position_y", 2430.0);
    this->declare_parameter<std::double_t> ("cylinder2_position_z", 5.0);
    this->declare_parameter<std::double_t> ("cylinder2_axis_x", -5.0);
    this->declare_parameter<std::double_t> ("cylinder2_axis_y", 4.0);
    this->declare_parameter<std::double_t> ("cylinder2_axis_z", 3.0);
    this->cylinder2_axis_x = this->get_parameter("cylinder2_axis_x").as_double();
    this->cylinder2_axis_y = this->get_parameter("cylinder2_axis_y").as_double();
    this->cylinder2_axis_z = this->get_parameter("cylinder2_axis_z").as_double();
    this->cylinder2_position_z = this->get_parameter("cylinder2_position_z").as_double();
    this->cylinder2_position_y = this->get_parameter("cylinder2_position_y").as_double();
    this->cylinder2_position_x = this->get_parameter("cylinder2_position_x").as_double();
    this->cylinder2_color_b = this->get_parameter("cylinder2_color_b").as_double();
    this->cylinder2_color_g = this->get_parameter("cylinder2_color_g").as_double();
    this->cylinder2_color_r = this->get_parameter("cylinder2_color_r").as_double();
    this->cylinder2_scale_z = this->get_parameter("cylinder2_scale_z").as_double();
    this->cylinder2_scale_y = this->get_parameter("cylinder2_scale_y").as_double();
    this->cylinder2_scale_x = this->get_parameter("cylinder2_scale_x").as_double();

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

    //debug
    this->length = 0.0;

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

        //debug 
        RCLCPP_INFO(this->get_logger(), "length: %f", this->length);
        RCLCPP_INFO(this->get_logger(), "temp_joint.length: %f", temp_joint.length);

    };

    //debug 
    RCLCPP_INFO(this->get_logger(), "length: %f", length);

    this->transform_joints_to_world.push_back(this->transform_joints_to_world[joint_number-1]*this->joints[joint_number-1].transform);
    this->transform_world_to_joints.push_back(this->joints[joint_number-1].transform.inverse()*this->transform_world_to_joints[joint_number-1]);

    this->base_visualization_pub=this->create_publisher<visualization_msgs::msg::Marker>("base_visualization",1);
    this->cdcr_plat_visualization_pub=this->create_publisher<visualization_msgs::msg::MarkerArray>("cdcr_plat_visualization",1);
    this->cdcr_point_visualization_pub=this->create_publisher<visualization_msgs::msg::Marker>("cdcr_point_visualization",1);
    this->deviation_marker_pub = this->create_publisher<visualization_msgs::msg::MarkerArray>("deviation_markers", 1);
    this->path_point_markers_pub = this->create_publisher<visualization_marker>("path_point_markers", 1);
    this->max_deviation_pub = this->create_publisher<std_msgs::msg::Float64>("max_deviation", 1);
    this->fit_time_pub = this->create_publisher<std_msgs::msg::Float64>("fit_time", 1);
    this->cylinder1_obstacle_visualization_pub = this->create_publisher<visualization_marker>("cylinder1_obstacle_marker", 1);
    this->cylinder2_obstacle_visualization_pub = this->create_publisher<visualization_marker>("cylinder2_obstacle_marker", 1);
    
    //debug
    temp_b_spline_interval_points_pub = this->create_publisher<visualization_marker>("b_spline_interval_points", 1);
    std::cout << "init finished !!!" << std::endl;

    return;
}


void CDCR::discretePath()
{
    path_points.clear();
    // Generate the base travel part path;
    int base_path_point_size = ceil((base_path_point_end-base_path_point_start).norm()/this->sample_interval);
    for (int i=0;i<=base_path_point_size;i++)
    {
        Eigen::Vector3d temp_path_point = (double)(base_path_point_size-i)/(double)base_path_point_size*base_path_point_start
                                            +(double)i/(double)base_path_point_size*base_path_point_end;
        path_points.push_back(temp_path_point);
    }
    switch (this->experience_type)
    {
    // case 1 is using the combination of line and circle;
    case 1:
    {
        double rad_theta = arc_path_theta/180.0*M_PI;
        double rad_alpha = arc_path_alpha/180.0*M_PI;
        int arc_path_point_size = ceil(std::abs(rad_theta) * this->arc_path_radius/this->sample_interval);
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
        break;
    }
    // case 2 is using the B-spline;
    case 2:
    {
        //debug
        RCLCPP_INFO(this->get_logger(), "here: 461");
        
        this->ctrl_points.col(0) = this->path_points.back();
        
        //debug
        RCLCPP_INFO(this->get_logger(), "here: 467");
        
        int orders = 3;
        this->b_spline_path.setUniformBspline(ctrl_points, orders, this->time_interval);
        double b_spline_length = 0.0;
        double temp_t=0.005;
        Eigen::Vector3d temp_last_path_point = path_points.back();
        Eigen::Vector3d temp_path_point;
        double time_span = b_spline_path.getTimeSum();
        Eigen::Vector3d temp_last_b_spline_point = this->ctrl_points.col(this->number_ctrl_points-1);
        
        //debug
        RCLCPP_INFO(this->get_logger(), "here: 478");
        
        do{
            temp_path_point = b_spline_path.evaluateDeBoorT(temp_t);

            //debug
            RCLCPP_INFO(this->get_logger(), "time_span: %f", time_span);
            RCLCPP_INFO(this->get_logger(), "temp_path_point:[%f, %f, %f]", temp_path_point.x(),temp_path_point.y(),temp_path_point.z());

            b_spline_length += (temp_path_point-temp_last_path_point).norm();

            //debug 
            RCLCPP_INFO(this->get_logger(), "b_spline_length: %f", b_spline_length);

            if (b_spline_length >= 1.0)
            {
                path_points.push_back(temp_path_point);

                // //debug
                // visualPathMarkers();
                // rclcpp::sleep_for(std::chrono::nanoseconds(100000000));

                b_spline_length = 0.0;
                
                // //debug
                // visualPathMarkers();
                // rclcpp::sleep_for(std::chrono::nanoseconds(10000000));
                
            }
            temp_last_path_point = temp_path_point;
            temp_t += 0.005;

            //debug
            RCLCPP_INFO(this->get_logger(), "here: 492");
            RCLCPP_INFO(this->get_logger(), " count: %f", (temp_t+0.0001)/0.005);
            RCLCPP_INFO(this->get_logger(), " temp_t: %f", temp_t);

        }while((temp_path_point-temp_last_b_spline_point).norm() > 1.0 && temp_t < time_span);

        //debug
        RCLCPP_INFO(this->get_logger(), "temp_last_b_spline_point: [%f, %f, %f]",temp_last_b_spline_point.x(),
                                                                                temp_last_b_spline_point.y(),
                                                                                temp_last_b_spline_point.z());
        RCLCPP_INFO(this->get_logger(), "here: 483");

        //debug
        RCLCPP_INFO(this->get_logger(), "519:");

        // // debug
        // visualPathMarkers();
        // rclcpp::sleep_for(std::chrono::nanoseconds(1000000000000));
        // rclcpp::shutdown();

        break;
    }
    // default
    default:
    {
        break;        
    }
    }
    // flag_discretized=true;
    return;
}


void CDCR::path_follow_exeperience()
{
    std::vector<double> experience_deviations;
    std::vector<double> experience_arc_radiuses;
    std::vector<double> time_spend;
    std::vector<double> theta_per_fit;
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
        // //debug: to save the experience data;
        // for (int i=0;i<experience_arc_radiuses.size();i++)
        // {
        //     per_radius_fit_time_ofs << time_spend[i] << "\n";
        //     per_radius_max_deviation_ofs << experience_deviations[i] << "\n";
        //     arc_radius_ofs << experience_arc_radiuses[i] << "\n";
        // }
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
    path.points.clear();
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

void CDCR::getCorrectTravelPointID()
{

    //debug
    int temp_count = 0;
    RCLCPP_INFO(this->get_logger(), "637:");

    Eigen::Vector3d path_tangent_vec;
    double path_deviation;

    for (int i=1;i<path_points.size()-1;i++)
    {
        //debug
        temp_count++;

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

            //debug
            RCLCPP_INFO(this->get_logger(), "658:");
            RCLCPP_INFO(this->get_logger(), "count: %d", temp_count);

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

        //debug
        RCLCPP_INFO(this->get_logger(), "getCorrectTravelPointID");

        return;
    }
}

void CDCR::path_follow(double& time_spend, double& max_deviation)
{
    RCLCPP_INFO(this->get_logger(), "path_follow: ");
    int fit_times=0;
    std::vector<int> max_deviation_path_point_ids;
    std::vector<double> max_deviations;
    std::vector<double> theta_per_fit;

    for (this->track_path_point_id=this->start_track_path_point_id;this->track_path_point_id < this->correct_end_path_point_id;this->track_path_point_id++)
    {
        // get base transform of base to world from the path point;
        getBasePose();

        // start to fit the cdcr robot;
        rclcpp::Time t_start = this->now();
        fitCDCR();
        rclcpp::Time t_end = this->now();
        double t_spend = t_end.seconds()-t_start.seconds();
        if (experience_type == 2)
        {
            theta_per_fit.push_back(this->joints[4].theta);
        }
        //debug
        RCLCPP_INFO(this->get_logger(), "fit_time: %f", t_spend);

        // debug
        std_msgs::msg::Float64 t_spend_msg;
        t_spend_msg.data = t_spend;
        this->fit_time_pub->publish(t_spend_msg);
        
        time_spend += t_spend;
        fit_times++;
        get_cdcr_sample_points();

        if (visualization_flag != 0)
        {
            rclcpp::Time visual_t_start = this->now();
            visualization();
            rclcpp::Time visual_t_end = this->now();
        }

        double temp_max_deviation = 0.0;
        int temp_max_deviation_path_point_id = 0;
        cal_deviation_get_max_deviation_path_point_id(temp_max_deviation,temp_max_deviation_path_point_id);

        //debug
        std_msgs::msg::Float64 max_deviation_msg;
        max_deviation_msg.data = temp_max_deviation;
        this->max_deviation_pub->publish(max_deviation_msg);
        
        max_deviations.push_back(temp_max_deviation);
        max_deviation_path_point_ids.push_back(temp_max_deviation_path_point_id);

        this->flag_first_fit = false;
    }

    // //debug: see the max_deviations
    // if (this->experience_type == 1)
    // {
    //     if (arc_path_radius >= 66.0 && arc_path_radius <= 70.0)
    //     {
    //         show_max_deviations(max_deviations,max_deviation_path_point_ids); 
            
    //         rclcpp::sleep_for(std::chrono::nanoseconds(10000000000));
    //     }
    // }

    time_spend = time_spend/(double)fit_times;
    RCLCPP_INFO(this->get_logger(), "fit_times: %d" , fit_times);
    RCLCPP_INFO(this->get_logger(), "time_spend: %f" , time_spend);
    max_deviation = *(std::max_element(max_deviations.begin(),max_deviations.end()));

    //debug: show max_deviation of direction model and no direction model
    RCLCPP_INFO(this->get_logger(), "max_deviation: %f", max_deviation);
    rclcpp::sleep_for(std::chrono::seconds(1));

    // //debug: save the max_deviations
    // if(this->experience_type == 2)
    // {   
    //     for (int i=0;i<max_deviations.size();i++)
    //     {
    //         per_fitperiod_theta_value_ofs << theta_per_fit[i] << "\n";
    //         per_fitperiod_max_deviation_ofs << max_deviations[i] << "\n";
    //     }
    // }
    // RCLCPP_INFO(this->get_logger(), "max_deviation: %f", max_deviation);
    
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
    this->cdcr_points.clear();
    this->cdcr_points.push_back(this->transform_base_to_world.block(0,3,3,1));
    this->cdcr_segment_point_id.clear();
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
    base_visual_msg.pose.position.y = base_box_center_position.y()-cdcr_plat_size_z/2.0-2;
    base_visual_msg.pose.position.z = base_box_center_position.z();

    Eigen::Matrix3d rotate_base_to_world(this->transform_base_to_world.block(0,0,3,3));
    Eigen::Quaterniond base_box_quaternion(rotate_base_to_world);
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
    for (int i=0;i<this->cdcr_segment_point_id.size();i++)
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

    if (experience_type == 2)
    {
        // visualize the b-spline path points;
        visualization_msgs::msg::Marker b_spline_interval_points_msg;
        b_spline_interval_points_msg.header = temp_header;
        b_spline_interval_points_msg.type = visualization_msgs::msg::Marker::SPHERE_LIST;
        b_spline_interval_points_msg.color.r = 0.2;
        b_spline_interval_points_msg.color.g = 0.8;
        b_spline_interval_points_msg.color.b = 0.2;
        b_spline_interval_points_msg.color.a = 1.0;
        b_spline_interval_points_msg.scale.x = 10.0;
        b_spline_interval_points_msg.scale.y = 10.0;
        b_spline_interval_points_msg.scale.z = 10.0;
        b_spline_interval_points_msg.pose.orientation.w = 1.0;
        b_spline_interval_points_msg.pose.orientation.x = 0.0;
        b_spline_interval_points_msg.pose.orientation.y = 0.0;
        b_spline_interval_points_msg.pose.orientation.z = 0.0;
        for (int i=0; i<this->b_spline_path_interval_points.size();i++)
        {
            geometry_msgs::msg::Point temp_point;
            temp_point.x = this->b_spline_path_interval_points[i].x();
            temp_point.y = this->b_spline_path_interval_points[i].y();
            temp_point.z = this->b_spline_path_interval_points[i].z();
            b_spline_interval_points_msg.points.push_back(temp_point);
        }   
        if (flag_visualize_b_spline_marker!=0)
            this->temp_b_spline_interval_points_pub->publish(b_spline_interval_points_msg); 

        //visualize the cylinder1 obstacle
        visualization_marker obstacle_cylinder1;
        obstacle_cylinder1.type = visualization_marker::CYLINDER;
        obstacle_cylinder1.action = visualization_marker::ADD;
        obstacle_cylinder1.header = temp_header;
        obstacle_cylinder1.color.r = this->cylinder1_color_r;
        obstacle_cylinder1.color.b = this->cylinder1_color_b;
        obstacle_cylinder1.color.g = this->cylinder1_color_g;
        obstacle_cylinder1.color.a = 1.0;
        obstacle_cylinder1.scale.x = this->cylinder1_scale_x;
        obstacle_cylinder1.scale.y = this->cylinder1_scale_y;
        obstacle_cylinder1.scale.z = this->cylinder1_scale_z;
        obstacle_cylinder1.pose.position.x = this->cylinder1_position_x;
        obstacle_cylinder1.pose.position.y = this->cylinder1_position_y;
        obstacle_cylinder1.pose.position.z = this->cylinder1_position_z;
        Eigen::Vector3d temp_axis1, rotation_axis1;
        temp_axis1 << cylinder1_axis_x, cylinder1_axis_y, cylinder1_axis_z;
        rotation_axis1 = Eigen::Vector3d(0,0,1.0).cross(temp_axis1.normalized()).normalized();
        double rotation_angle1 = acos(temp_axis1.normalized().dot(Eigen::Vector3d(0.0,0.0,1.0)));
        Eigen::Matrix3d rotation1 = Eigen::AngleAxisd(rotation_angle1, rotation_axis1).toRotationMatrix();
        Eigen::Quaterniond temp_q1(rotation1);
        obstacle_cylinder1.pose.orientation.x = temp_q1.x();
        obstacle_cylinder1.pose.orientation.y = temp_q1.y();
        obstacle_cylinder1.pose.orientation.z = temp_q1.z();
        obstacle_cylinder1.pose.orientation.w = temp_q1.w();
        this->cylinder1_obstacle_visualization_pub->publish(obstacle_cylinder1);

        //debug
        RCLCPP_INFO(this->get_logger(), "1004:");

        //visualize the cylinder2 obstacle
        visualization_marker obstacle_cylinder2;
        obstacle_cylinder2.type = visualization_marker::CYLINDER;
        obstacle_cylinder2.action = visualization_marker::ADD;
        obstacle_cylinder2.header = temp_header;
        obstacle_cylinder2.color.r = this->cylinder2_color_r;
        obstacle_cylinder2.color.b = this->cylinder2_color_b;
        obstacle_cylinder2.color.g = this->cylinder2_color_g;
        obstacle_cylinder2.color.a = 1.0;
        obstacle_cylinder2.scale.x = this->cylinder2_scale_x;
        obstacle_cylinder2.scale.y = this->cylinder2_scale_y;
        obstacle_cylinder2.scale.z = this->cylinder2_scale_z;
        obstacle_cylinder2.pose.position.x = this->cylinder2_position_x;
        obstacle_cylinder2.pose.position.y = this->cylinder2_position_y;
        obstacle_cylinder2.pose.position.z = this->cylinder2_position_z;
        Eigen::Vector3d temp_axis2, rotation_axis2;
        temp_axis2 << cylinder2_axis_x, cylinder2_axis_y, cylinder2_axis_z;
        rotation_axis2 = Eigen::Vector3d(0,0,1.0).cross(temp_axis2.normalized()).normalized();
        double rotation_angle2 = acos(temp_axis2.normalized().dot(Eigen::Vector3d(0.0,0.0,1.0)));
        Eigen::Matrix3d rotation2 = Eigen::AngleAxisd(rotation_angle2, rotation_axis2).toRotationMatrix();
        Eigen::Quaterniond temp_q2(rotation2);
        obstacle_cylinder2.pose.orientation.x = temp_q2.x();
        obstacle_cylinder2.pose.orientation.y = temp_q2.y();
        obstacle_cylinder2.pose.orientation.z = temp_q2.z();
        obstacle_cylinder2.pose.orientation.w = temp_q2.w();
        this->cylinder2_obstacle_visualization_pub->publish(obstacle_cylinder2);

        //debug
        RCLCPP_INFO(this->get_logger(), "1034:");


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

    // in case the joint variate change extremelly, we use the last fit result as the wrong value.
    double temp_theta = 0.0, temp_alpha = 0.0;
    
    for (int joint_id=0; joint_id<joint_number; joint_id++)
    {
        //debug: find why the fit result change so extremelly
        temp_theta = this->joints[joint_id].theta;
        temp_alpha = this->joints[joint_id].alpha;

        int target_path_point_id = segment_start_path_point_id+ceil(this->joints[joint_id].length/this->sample_interval);
        Eigen::Vector4d target_position;
        target_position << path_points[target_path_point_id],1.0;
        
        Eigen::Vector3d target_tangent_vec=(path_points[target_path_point_id+1]-path_points[target_path_point_id-1]).normalized();
        // transform the target_postion and tangent_vec to the frame of joint[joint_id]
        target_position = transform_world_to_joints[joint_id]*target_position;
        target_tangent_vec = transform_world_to_joints[joint_id].block(0,0,3,3)*target_tangent_vec;
        ceres::Problem fit_problem;
        fit_problem.AddResidualBlock(
            new ceres::AutoDiffCostFunction<position_residual,3,1,1>(
                new position_residual(
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
        // // here give the range straint of alpha variate will cause the optimal space of alpha is't discontinuous.
        // fit_problem.SetParameterLowerBound(&joints[joint_id].alpha, 0, this->alpha_lower_bound);
        fit_problem.SetParameterLowerBound(&joints[joint_id].theta, 0, this->theta_lower_bound);
        // fit_problem.SetParameterUpperBound(&joints[joint_id].alpha, 0, this->alpha_upper_bound);
        fit_problem.SetParameterUpperBound(&joints[joint_id].theta, 0, this->theta_upper_bound);
        ceres::Solver::Options option;
        option.max_num_iterations=50;
        option.minimizer_progress_to_stdout = false;
        option.linear_solver_type=ceres::CGNR;
        // option.linear_solver_type=ceres::DENSE_QR;
        // option.linear_solver_type=ceres::DENSE_NORMAL_CHOLESKY;
        // option.linear_solver_type=ceres::ITERATIVE_SCHUR;
        // option.linear_solver_type=ceres::DENSE_SCHUR;
        // option.trust_region_strategy_type=ceres::DOGLEG;
        option.logging_type=ceres::SILENT;
        ceres::Solver::Summary summary;
        ceres::Solve(option,&fit_problem,&summary);

        // if theta out range, need changing the theta value to the correct range.
        if (joints[joint_id].theta < 0)
        {
            joints[joint_id].theta = std::abs(joints[joint_id].theta);
            joints[joint_id].alpha = (joints[joint_id].alpha + M_PI) > M_PI ?  (joints[joint_id].alpha-M_PI) : (joints[joint_id].alpha+M_PI);
        }
        // if alpha out range, need changing the alpha value to the correct range.
        do{
            if (joints[joint_id].alpha < this->alpha_lower_bound)
            {
                joints[joint_id].alpha += 2*M_PI;
            }
            if (joints[joint_id].alpha > this->alpha_upper_bound)
            {
                joints[joint_id].alpha -= 2*M_PI;
            }
        }while(joints[joint_id].alpha < this->alpha_lower_bound || joints[joint_id].alpha > this->alpha_upper_bound);

        Eigen::Vector3d joint_end_position;
        transform_joints_to_world[joint_id+1] = transform_joints_to_world[joint_id] * joints[joint_id].getTransform();
        transform_world_to_joints[joint_id+1] = joints[joint_id].transform.inverse()*transform_world_to_joints[joint_id];            
        joint_end_position = transform_joints_to_world[joint_id+1].block(0,3,3,1);
        find_closed_path_point(target_path_point_id,joint_end_position,segment_start_path_point_id);
    }
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
    if (this->length + this->safe_path_length_redundance > (double)(path_points.size()-path_point_id)*sample_interval)
    {

        //debug
        RCLCPP_INFO(this->get_logger(), "length: %f", this->length);
        RCLCPP_INFO(this->get_logger(), "safe_path_length_redundance: %f", this->safe_path_length_redundance);
        RCLCPP_INFO(this->get_logger(), "path_points.size(): %d", path_points.size());
        RCLCPP_INFO(this->get_logger(), "path_point_id: %d", path_point_id);

        return false;
    }
    return true;
}