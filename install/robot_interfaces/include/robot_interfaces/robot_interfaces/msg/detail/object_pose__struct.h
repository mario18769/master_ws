// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_interfaces:msg/ObjectPose.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_interfaces/msg/object_pose.h"


#ifndef ROBOT_INTERFACES__MSG__DETAIL__OBJECT_POSE__STRUCT_H_
#define ROBOT_INTERFACES__MSG__DETAIL__OBJECT_POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'object_type'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/ObjectPose in the package robot_interfaces.
typedef struct robot_interfaces__msg__ObjectPose
{
  rosidl_runtime_c__String object_type;
  double axis_x;
  double axis_y;
  double axis_z;
  double axis_pt_x;
  double axis_pt_y;
  double axis_pt_z;
  double axis2_x;
  double axis2_y;
  double axis2_z;
  double radius;
  double length;
  double mid_x;
  double mid_y;
  double mid_z;
} robot_interfaces__msg__ObjectPose;

// Struct for a sequence of robot_interfaces__msg__ObjectPose.
typedef struct robot_interfaces__msg__ObjectPose__Sequence
{
  robot_interfaces__msg__ObjectPose * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_interfaces__msg__ObjectPose__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_INTERFACES__MSG__DETAIL__OBJECT_POSE__STRUCT_H_
