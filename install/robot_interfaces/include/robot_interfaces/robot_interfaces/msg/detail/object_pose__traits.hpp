// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_interfaces:msg/ObjectPose.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_interfaces/msg/object_pose.hpp"


#ifndef ROBOT_INTERFACES__MSG__DETAIL__OBJECT_POSE__TRAITS_HPP_
#define ROBOT_INTERFACES__MSG__DETAIL__OBJECT_POSE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_interfaces/msg/detail/object_pose__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace robot_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ObjectPose & msg,
  std::ostream & out)
{
  out << "{";
  // member: object_type
  {
    out << "object_type: ";
    rosidl_generator_traits::value_to_yaml(msg.object_type, out);
    out << ", ";
  }

  // member: axis_x
  {
    out << "axis_x: ";
    rosidl_generator_traits::value_to_yaml(msg.axis_x, out);
    out << ", ";
  }

  // member: axis_y
  {
    out << "axis_y: ";
    rosidl_generator_traits::value_to_yaml(msg.axis_y, out);
    out << ", ";
  }

  // member: axis_z
  {
    out << "axis_z: ";
    rosidl_generator_traits::value_to_yaml(msg.axis_z, out);
    out << ", ";
  }

  // member: axis_pt_x
  {
    out << "axis_pt_x: ";
    rosidl_generator_traits::value_to_yaml(msg.axis_pt_x, out);
    out << ", ";
  }

  // member: axis_pt_y
  {
    out << "axis_pt_y: ";
    rosidl_generator_traits::value_to_yaml(msg.axis_pt_y, out);
    out << ", ";
  }

  // member: axis_pt_z
  {
    out << "axis_pt_z: ";
    rosidl_generator_traits::value_to_yaml(msg.axis_pt_z, out);
    out << ", ";
  }

  // member: axis2_x
  {
    out << "axis2_x: ";
    rosidl_generator_traits::value_to_yaml(msg.axis2_x, out);
    out << ", ";
  }

  // member: axis2_y
  {
    out << "axis2_y: ";
    rosidl_generator_traits::value_to_yaml(msg.axis2_y, out);
    out << ", ";
  }

  // member: axis2_z
  {
    out << "axis2_z: ";
    rosidl_generator_traits::value_to_yaml(msg.axis2_z, out);
    out << ", ";
  }

  // member: radius
  {
    out << "radius: ";
    rosidl_generator_traits::value_to_yaml(msg.radius, out);
    out << ", ";
  }

  // member: length
  {
    out << "length: ";
    rosidl_generator_traits::value_to_yaml(msg.length, out);
    out << ", ";
  }

  // member: mid_x
  {
    out << "mid_x: ";
    rosidl_generator_traits::value_to_yaml(msg.mid_x, out);
    out << ", ";
  }

  // member: mid_y
  {
    out << "mid_y: ";
    rosidl_generator_traits::value_to_yaml(msg.mid_y, out);
    out << ", ";
  }

  // member: mid_z
  {
    out << "mid_z: ";
    rosidl_generator_traits::value_to_yaml(msg.mid_z, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ObjectPose & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: object_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "object_type: ";
    rosidl_generator_traits::value_to_yaml(msg.object_type, out);
    out << "\n";
  }

  // member: axis_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "axis_x: ";
    rosidl_generator_traits::value_to_yaml(msg.axis_x, out);
    out << "\n";
  }

  // member: axis_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "axis_y: ";
    rosidl_generator_traits::value_to_yaml(msg.axis_y, out);
    out << "\n";
  }

  // member: axis_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "axis_z: ";
    rosidl_generator_traits::value_to_yaml(msg.axis_z, out);
    out << "\n";
  }

  // member: axis_pt_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "axis_pt_x: ";
    rosidl_generator_traits::value_to_yaml(msg.axis_pt_x, out);
    out << "\n";
  }

  // member: axis_pt_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "axis_pt_y: ";
    rosidl_generator_traits::value_to_yaml(msg.axis_pt_y, out);
    out << "\n";
  }

  // member: axis_pt_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "axis_pt_z: ";
    rosidl_generator_traits::value_to_yaml(msg.axis_pt_z, out);
    out << "\n";
  }

  // member: axis2_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "axis2_x: ";
    rosidl_generator_traits::value_to_yaml(msg.axis2_x, out);
    out << "\n";
  }

  // member: axis2_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "axis2_y: ";
    rosidl_generator_traits::value_to_yaml(msg.axis2_y, out);
    out << "\n";
  }

  // member: axis2_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "axis2_z: ";
    rosidl_generator_traits::value_to_yaml(msg.axis2_z, out);
    out << "\n";
  }

  // member: radius
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "radius: ";
    rosidl_generator_traits::value_to_yaml(msg.radius, out);
    out << "\n";
  }

  // member: length
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "length: ";
    rosidl_generator_traits::value_to_yaml(msg.length, out);
    out << "\n";
  }

  // member: mid_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mid_x: ";
    rosidl_generator_traits::value_to_yaml(msg.mid_x, out);
    out << "\n";
  }

  // member: mid_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mid_y: ";
    rosidl_generator_traits::value_to_yaml(msg.mid_y, out);
    out << "\n";
  }

  // member: mid_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mid_z: ";
    rosidl_generator_traits::value_to_yaml(msg.mid_z, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ObjectPose & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace robot_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use robot_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robot_interfaces::msg::ObjectPose & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const robot_interfaces::msg::ObjectPose & msg)
{
  return robot_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robot_interfaces::msg::ObjectPose>()
{
  return "robot_interfaces::msg::ObjectPose";
}

template<>
inline const char * name<robot_interfaces::msg::ObjectPose>()
{
  return "robot_interfaces/msg/ObjectPose";
}

template<>
struct has_fixed_size<robot_interfaces::msg::ObjectPose>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_interfaces::msg::ObjectPose>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_interfaces::msg::ObjectPose>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_INTERFACES__MSG__DETAIL__OBJECT_POSE__TRAITS_HPP_
