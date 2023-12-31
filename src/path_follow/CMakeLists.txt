cmake_minimum_required(VERSION 3.5)
project(path_follow)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(Eigen3 3.3.7 REQUIRED)
find_package(Sophus REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(Ceres REQUIRED)
find_package(cv_bridge REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

include_directories(${EIGEN3_INCLUDE_DIR} ${Sophus_DIR} ${CERES_INCLUDE_DIRS})

add_executable(path_follow src/main.cpp src/cdcr.cpp src/joint.cpp src/uniform_bspline.cpp)

ament_target_dependencies(path_follow rclcpp nav_msgs rclcpp_components geometry_msgs std_msgs visualization_msgs cv_bridge)

target_link_libraries(path_follow ${EIGEN_LIBS} ${CERES_LIBRARIES})

install(TARGETS
  path_follow
  DESTINATION
  lib/${PROJECT_NAME}
)
install(DIRECTORY
  launch
  DESTINATION
  share/${PROJECT_NAME}
)
ament_package()
