cmake_minimum_required(VERSION 3.8)
project(estun_control)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(moveit REQUIRED)
find_package(std_msgs REQUIRED)
find_package(moveit_msgs REQUIRED)
find_package(moveit_ros_planning_interface  REQUIRED )
find_package(geometric_shapes  REQUIRED )
find_package(geometry_msgs  REQUIRED )
find_package(tf2_ros  REQUIRED )
find_package(tf2  REQUIRED )
find_package(Boost REQUIRED thread)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

add_executable( cartesian_planner src/cartesian_planner.cpp ) 
ament_target_dependencies(cartesian_planner rclcpp std_msgs moveit_ros_planning_interface)

add_executable( obstacle_planner src/obstacle_planner.cpp ) 
ament_target_dependencies(obstacle_planner 
rclcpp 
std_msgs 
moveit_ros_planning_interface
moveit_msgs
moveit
geometric_shapes
geometry_msgs
tf2_ros
tf2)

target_link_libraries(obstacle_planner Boost::thread)

install(DIRECTORY launch  
  DESTINATION share/${PROJECT_NAME}
)

install(DIRECTORY meshes
  DESTINATION share/${PROJECT_NAME}
)

install(TARGETS cartesian_planner
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS obstacle_planner
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
