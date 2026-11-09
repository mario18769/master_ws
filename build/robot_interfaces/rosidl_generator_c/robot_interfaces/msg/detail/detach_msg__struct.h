// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_interfaces:msg/DetachMsg.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_interfaces/msg/detach_msg.h"


#ifndef ROBOT_INTERFACES__MSG__DETAIL__DETACH_MSG__STRUCT_H_
#define ROBOT_INTERFACES__MSG__DETAIL__DETACH_MSG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'attach_msg'
// Member 'detach_msg'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/DetachMsg in the package robot_interfaces.
typedef struct robot_interfaces__msg__DetachMsg
{
  rosidl_runtime_c__String attach_msg;
  rosidl_runtime_c__String detach_msg;
} robot_interfaces__msg__DetachMsg;

// Struct for a sequence of robot_interfaces__msg__DetachMsg.
typedef struct robot_interfaces__msg__DetachMsg__Sequence
{
  robot_interfaces__msg__DetachMsg * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_interfaces__msg__DetachMsg__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_INTERFACES__MSG__DETAIL__DETACH_MSG__STRUCT_H_
