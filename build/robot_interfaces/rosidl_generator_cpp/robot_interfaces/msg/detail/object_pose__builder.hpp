// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_interfaces:msg/ObjectPose.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_interfaces/msg/object_pose.hpp"


#ifndef ROBOT_INTERFACES__MSG__DETAIL__OBJECT_POSE__BUILDER_HPP_
#define ROBOT_INTERFACES__MSG__DETAIL__OBJECT_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_interfaces/msg/detail/object_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_interfaces
{

namespace msg
{

namespace builder
{

class Init_ObjectPose_mid_z
{
public:
  explicit Init_ObjectPose_mid_z(::robot_interfaces::msg::ObjectPose & msg)
  : msg_(msg)
  {}
  ::robot_interfaces::msg::ObjectPose mid_z(::robot_interfaces::msg::ObjectPose::_mid_z_type arg)
  {
    msg_.mid_z = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_interfaces::msg::ObjectPose msg_;
};

class Init_ObjectPose_mid_y
{
public:
  explicit Init_ObjectPose_mid_y(::robot_interfaces::msg::ObjectPose & msg)
  : msg_(msg)
  {}
  Init_ObjectPose_mid_z mid_y(::robot_interfaces::msg::ObjectPose::_mid_y_type arg)
  {
    msg_.mid_y = std::move(arg);
    return Init_ObjectPose_mid_z(msg_);
  }

private:
  ::robot_interfaces::msg::ObjectPose msg_;
};

class Init_ObjectPose_mid_x
{
public:
  explicit Init_ObjectPose_mid_x(::robot_interfaces::msg::ObjectPose & msg)
  : msg_(msg)
  {}
  Init_ObjectPose_mid_y mid_x(::robot_interfaces::msg::ObjectPose::_mid_x_type arg)
  {
    msg_.mid_x = std::move(arg);
    return Init_ObjectPose_mid_y(msg_);
  }

private:
  ::robot_interfaces::msg::ObjectPose msg_;
};

class Init_ObjectPose_length
{
public:
  explicit Init_ObjectPose_length(::robot_interfaces::msg::ObjectPose & msg)
  : msg_(msg)
  {}
  Init_ObjectPose_mid_x length(::robot_interfaces::msg::ObjectPose::_length_type arg)
  {
    msg_.length = std::move(arg);
    return Init_ObjectPose_mid_x(msg_);
  }

private:
  ::robot_interfaces::msg::ObjectPose msg_;
};

class Init_ObjectPose_radius
{
public:
  explicit Init_ObjectPose_radius(::robot_interfaces::msg::ObjectPose & msg)
  : msg_(msg)
  {}
  Init_ObjectPose_length radius(::robot_interfaces::msg::ObjectPose::_radius_type arg)
  {
    msg_.radius = std::move(arg);
    return Init_ObjectPose_length(msg_);
  }

private:
  ::robot_interfaces::msg::ObjectPose msg_;
};

class Init_ObjectPose_axis2_z
{
public:
  explicit Init_ObjectPose_axis2_z(::robot_interfaces::msg::ObjectPose & msg)
  : msg_(msg)
  {}
  Init_ObjectPose_radius axis2_z(::robot_interfaces::msg::ObjectPose::_axis2_z_type arg)
  {
    msg_.axis2_z = std::move(arg);
    return Init_ObjectPose_radius(msg_);
  }

private:
  ::robot_interfaces::msg::ObjectPose msg_;
};

class Init_ObjectPose_axis2_y
{
public:
  explicit Init_ObjectPose_axis2_y(::robot_interfaces::msg::ObjectPose & msg)
  : msg_(msg)
  {}
  Init_ObjectPose_axis2_z axis2_y(::robot_interfaces::msg::ObjectPose::_axis2_y_type arg)
  {
    msg_.axis2_y = std::move(arg);
    return Init_ObjectPose_axis2_z(msg_);
  }

private:
  ::robot_interfaces::msg::ObjectPose msg_;
};

class Init_ObjectPose_axis2_x
{
public:
  explicit Init_ObjectPose_axis2_x(::robot_interfaces::msg::ObjectPose & msg)
  : msg_(msg)
  {}
  Init_ObjectPose_axis2_y axis2_x(::robot_interfaces::msg::ObjectPose::_axis2_x_type arg)
  {
    msg_.axis2_x = std::move(arg);
    return Init_ObjectPose_axis2_y(msg_);
  }

private:
  ::robot_interfaces::msg::ObjectPose msg_;
};

class Init_ObjectPose_axis_pt_z
{
public:
  explicit Init_ObjectPose_axis_pt_z(::robot_interfaces::msg::ObjectPose & msg)
  : msg_(msg)
  {}
  Init_ObjectPose_axis2_x axis_pt_z(::robot_interfaces::msg::ObjectPose::_axis_pt_z_type arg)
  {
    msg_.axis_pt_z = std::move(arg);
    return Init_ObjectPose_axis2_x(msg_);
  }

private:
  ::robot_interfaces::msg::ObjectPose msg_;
};

class Init_ObjectPose_axis_pt_y
{
public:
  explicit Init_ObjectPose_axis_pt_y(::robot_interfaces::msg::ObjectPose & msg)
  : msg_(msg)
  {}
  Init_ObjectPose_axis_pt_z axis_pt_y(::robot_interfaces::msg::ObjectPose::_axis_pt_y_type arg)
  {
    msg_.axis_pt_y = std::move(arg);
    return Init_ObjectPose_axis_pt_z(msg_);
  }

private:
  ::robot_interfaces::msg::ObjectPose msg_;
};

class Init_ObjectPose_axis_pt_x
{
public:
  explicit Init_ObjectPose_axis_pt_x(::robot_interfaces::msg::ObjectPose & msg)
  : msg_(msg)
  {}
  Init_ObjectPose_axis_pt_y axis_pt_x(::robot_interfaces::msg::ObjectPose::_axis_pt_x_type arg)
  {
    msg_.axis_pt_x = std::move(arg);
    return Init_ObjectPose_axis_pt_y(msg_);
  }

private:
  ::robot_interfaces::msg::ObjectPose msg_;
};

class Init_ObjectPose_axis_z
{
public:
  explicit Init_ObjectPose_axis_z(::robot_interfaces::msg::ObjectPose & msg)
  : msg_(msg)
  {}
  Init_ObjectPose_axis_pt_x axis_z(::robot_interfaces::msg::ObjectPose::_axis_z_type arg)
  {
    msg_.axis_z = std::move(arg);
    return Init_ObjectPose_axis_pt_x(msg_);
  }

private:
  ::robot_interfaces::msg::ObjectPose msg_;
};

class Init_ObjectPose_axis_y
{
public:
  explicit Init_ObjectPose_axis_y(::robot_interfaces::msg::ObjectPose & msg)
  : msg_(msg)
  {}
  Init_ObjectPose_axis_z axis_y(::robot_interfaces::msg::ObjectPose::_axis_y_type arg)
  {
    msg_.axis_y = std::move(arg);
    return Init_ObjectPose_axis_z(msg_);
  }

private:
  ::robot_interfaces::msg::ObjectPose msg_;
};

class Init_ObjectPose_axis_x
{
public:
  explicit Init_ObjectPose_axis_x(::robot_interfaces::msg::ObjectPose & msg)
  : msg_(msg)
  {}
  Init_ObjectPose_axis_y axis_x(::robot_interfaces::msg::ObjectPose::_axis_x_type arg)
  {
    msg_.axis_x = std::move(arg);
    return Init_ObjectPose_axis_y(msg_);
  }

private:
  ::robot_interfaces::msg::ObjectPose msg_;
};

class Init_ObjectPose_object_type
{
public:
  Init_ObjectPose_object_type()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ObjectPose_axis_x object_type(::robot_interfaces::msg::ObjectPose::_object_type_type arg)
  {
    msg_.object_type = std::move(arg);
    return Init_ObjectPose_axis_x(msg_);
  }

private:
  ::robot_interfaces::msg::ObjectPose msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_interfaces::msg::ObjectPose>()
{
  return robot_interfaces::msg::builder::Init_ObjectPose_object_type();
}

}  // namespace robot_interfaces

#endif  // ROBOT_INTERFACES__MSG__DETAIL__OBJECT_POSE__BUILDER_HPP_
