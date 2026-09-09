# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target moveit_task_constructor_msgs::moveit_task_constructor_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${moveit_task_constructor_msgs_TARGETS}.
if(moveit_task_constructor_msgs_TARGETS AND NOT TARGET moveit_task_constructor_msgs::moveit_task_constructor_msgs)
  add_library(moveit_task_constructor_msgs::moveit_task_constructor_msgs INTERFACE IMPORTED)
  set_target_properties(moveit_task_constructor_msgs::moveit_task_constructor_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${moveit_task_constructor_msgs_TARGETS}")
endif()
