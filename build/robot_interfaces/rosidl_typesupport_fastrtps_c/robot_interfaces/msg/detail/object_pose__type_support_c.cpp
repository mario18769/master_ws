// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from robot_interfaces:msg/ObjectPose.idl
// generated code does not contain a copyright notice
#include "robot_interfaces/msg/detail/object_pose__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "robot_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "robot_interfaces/msg/detail/object_pose__struct.h"
#include "robot_interfaces/msg/detail/object_pose__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/string.h"  // object_type
#include "rosidl_runtime_c/string_functions.h"  // object_type

// forward declare type support functions


using _ObjectPose__ros_msg_type = robot_interfaces__msg__ObjectPose;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_interfaces
bool cdr_serialize_robot_interfaces__msg__ObjectPose(
  const robot_interfaces__msg__ObjectPose * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: object_type
  {
    const rosidl_runtime_c__String * str = &ros_message->object_type;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: axis_x
  {
    cdr << ros_message->axis_x;
  }

  // Field name: axis_y
  {
    cdr << ros_message->axis_y;
  }

  // Field name: axis_z
  {
    cdr << ros_message->axis_z;
  }

  // Field name: axis_pt_x
  {
    cdr << ros_message->axis_pt_x;
  }

  // Field name: axis_pt_y
  {
    cdr << ros_message->axis_pt_y;
  }

  // Field name: axis_pt_z
  {
    cdr << ros_message->axis_pt_z;
  }

  // Field name: axis2_x
  {
    cdr << ros_message->axis2_x;
  }

  // Field name: axis2_y
  {
    cdr << ros_message->axis2_y;
  }

  // Field name: axis2_z
  {
    cdr << ros_message->axis2_z;
  }

  // Field name: radius
  {
    cdr << ros_message->radius;
  }

  // Field name: length
  {
    cdr << ros_message->length;
  }

  // Field name: mid_x
  {
    cdr << ros_message->mid_x;
  }

  // Field name: mid_y
  {
    cdr << ros_message->mid_y;
  }

  // Field name: mid_z
  {
    cdr << ros_message->mid_z;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_interfaces
bool cdr_deserialize_robot_interfaces__msg__ObjectPose(
  eprosima::fastcdr::Cdr & cdr,
  robot_interfaces__msg__ObjectPose * ros_message)
{
  // Field name: object_type
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->object_type.data) {
      rosidl_runtime_c__String__init(&ros_message->object_type);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->object_type,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'object_type'\n");
      return false;
    }
  }

  // Field name: axis_x
  {
    cdr >> ros_message->axis_x;
  }

  // Field name: axis_y
  {
    cdr >> ros_message->axis_y;
  }

  // Field name: axis_z
  {
    cdr >> ros_message->axis_z;
  }

  // Field name: axis_pt_x
  {
    cdr >> ros_message->axis_pt_x;
  }

  // Field name: axis_pt_y
  {
    cdr >> ros_message->axis_pt_y;
  }

  // Field name: axis_pt_z
  {
    cdr >> ros_message->axis_pt_z;
  }

  // Field name: axis2_x
  {
    cdr >> ros_message->axis2_x;
  }

  // Field name: axis2_y
  {
    cdr >> ros_message->axis2_y;
  }

  // Field name: axis2_z
  {
    cdr >> ros_message->axis2_z;
  }

  // Field name: radius
  {
    cdr >> ros_message->radius;
  }

  // Field name: length
  {
    cdr >> ros_message->length;
  }

  // Field name: mid_x
  {
    cdr >> ros_message->mid_x;
  }

  // Field name: mid_y
  {
    cdr >> ros_message->mid_y;
  }

  // Field name: mid_z
  {
    cdr >> ros_message->mid_z;
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_interfaces
size_t get_serialized_size_robot_interfaces__msg__ObjectPose(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ObjectPose__ros_msg_type * ros_message = static_cast<const _ObjectPose__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: object_type
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->object_type.size + 1);

  // Field name: axis_x
  {
    size_t item_size = sizeof(ros_message->axis_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: axis_y
  {
    size_t item_size = sizeof(ros_message->axis_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: axis_z
  {
    size_t item_size = sizeof(ros_message->axis_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: axis_pt_x
  {
    size_t item_size = sizeof(ros_message->axis_pt_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: axis_pt_y
  {
    size_t item_size = sizeof(ros_message->axis_pt_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: axis_pt_z
  {
    size_t item_size = sizeof(ros_message->axis_pt_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: axis2_x
  {
    size_t item_size = sizeof(ros_message->axis2_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: axis2_y
  {
    size_t item_size = sizeof(ros_message->axis2_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: axis2_z
  {
    size_t item_size = sizeof(ros_message->axis2_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: radius
  {
    size_t item_size = sizeof(ros_message->radius);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: length
  {
    size_t item_size = sizeof(ros_message->length);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: mid_x
  {
    size_t item_size = sizeof(ros_message->mid_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: mid_y
  {
    size_t item_size = sizeof(ros_message->mid_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: mid_z
  {
    size_t item_size = sizeof(ros_message->mid_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_interfaces
size_t max_serialized_size_robot_interfaces__msg__ObjectPose(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Field name: object_type
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Field name: axis_x
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: axis_y
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: axis_z
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: axis_pt_x
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: axis_pt_y
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: axis_pt_z
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: axis2_x
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: axis2_y
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: axis2_z
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: radius
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: length
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: mid_x
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: mid_y
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: mid_z
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = robot_interfaces__msg__ObjectPose;
    is_plain =
      (
      offsetof(DataType, mid_z) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_interfaces
bool cdr_serialize_key_robot_interfaces__msg__ObjectPose(
  const robot_interfaces__msg__ObjectPose * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: object_type
  {
    const rosidl_runtime_c__String * str = &ros_message->object_type;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: axis_x
  {
    cdr << ros_message->axis_x;
  }

  // Field name: axis_y
  {
    cdr << ros_message->axis_y;
  }

  // Field name: axis_z
  {
    cdr << ros_message->axis_z;
  }

  // Field name: axis_pt_x
  {
    cdr << ros_message->axis_pt_x;
  }

  // Field name: axis_pt_y
  {
    cdr << ros_message->axis_pt_y;
  }

  // Field name: axis_pt_z
  {
    cdr << ros_message->axis_pt_z;
  }

  // Field name: axis2_x
  {
    cdr << ros_message->axis2_x;
  }

  // Field name: axis2_y
  {
    cdr << ros_message->axis2_y;
  }

  // Field name: axis2_z
  {
    cdr << ros_message->axis2_z;
  }

  // Field name: radius
  {
    cdr << ros_message->radius;
  }

  // Field name: length
  {
    cdr << ros_message->length;
  }

  // Field name: mid_x
  {
    cdr << ros_message->mid_x;
  }

  // Field name: mid_y
  {
    cdr << ros_message->mid_y;
  }

  // Field name: mid_z
  {
    cdr << ros_message->mid_z;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_interfaces
size_t get_serialized_size_key_robot_interfaces__msg__ObjectPose(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ObjectPose__ros_msg_type * ros_message = static_cast<const _ObjectPose__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: object_type
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->object_type.size + 1);

  // Field name: axis_x
  {
    size_t item_size = sizeof(ros_message->axis_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: axis_y
  {
    size_t item_size = sizeof(ros_message->axis_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: axis_z
  {
    size_t item_size = sizeof(ros_message->axis_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: axis_pt_x
  {
    size_t item_size = sizeof(ros_message->axis_pt_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: axis_pt_y
  {
    size_t item_size = sizeof(ros_message->axis_pt_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: axis_pt_z
  {
    size_t item_size = sizeof(ros_message->axis_pt_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: axis2_x
  {
    size_t item_size = sizeof(ros_message->axis2_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: axis2_y
  {
    size_t item_size = sizeof(ros_message->axis2_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: axis2_z
  {
    size_t item_size = sizeof(ros_message->axis2_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: radius
  {
    size_t item_size = sizeof(ros_message->radius);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: length
  {
    size_t item_size = sizeof(ros_message->length);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: mid_x
  {
    size_t item_size = sizeof(ros_message->mid_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: mid_y
  {
    size_t item_size = sizeof(ros_message->mid_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: mid_z
  {
    size_t item_size = sizeof(ros_message->mid_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_interfaces
size_t max_serialized_size_key_robot_interfaces__msg__ObjectPose(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;
  // Field name: object_type
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Field name: axis_x
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: axis_y
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: axis_z
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: axis_pt_x
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: axis_pt_y
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: axis_pt_z
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: axis2_x
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: axis2_y
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: axis2_z
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: radius
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: length
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: mid_x
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: mid_y
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: mid_z
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = robot_interfaces__msg__ObjectPose;
    is_plain =
      (
      offsetof(DataType, mid_z) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _ObjectPose__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const robot_interfaces__msg__ObjectPose * ros_message = static_cast<const robot_interfaces__msg__ObjectPose *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_robot_interfaces__msg__ObjectPose(ros_message, cdr);
}

static bool _ObjectPose__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  robot_interfaces__msg__ObjectPose * ros_message = static_cast<robot_interfaces__msg__ObjectPose *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_robot_interfaces__msg__ObjectPose(cdr, ros_message);
}

static uint32_t _ObjectPose__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_robot_interfaces__msg__ObjectPose(
      untyped_ros_message, 0));
}

static size_t _ObjectPose__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_robot_interfaces__msg__ObjectPose(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_ObjectPose = {
  "robot_interfaces::msg",
  "ObjectPose",
  _ObjectPose__cdr_serialize,
  _ObjectPose__cdr_deserialize,
  _ObjectPose__get_serialized_size,
  _ObjectPose__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _ObjectPose__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ObjectPose,
  get_message_typesupport_handle_function,
  &robot_interfaces__msg__ObjectPose__get_type_hash,
  &robot_interfaces__msg__ObjectPose__get_type_description,
  &robot_interfaces__msg__ObjectPose__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_interfaces, msg, ObjectPose)() {
  return &_ObjectPose__type_support;
}

#if defined(__cplusplus)
}
#endif
