// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_interfaces:msg/DetachMsg.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_interfaces/msg/detach_msg.hpp"


#ifndef ROBOT_INTERFACES__MSG__DETAIL__DETACH_MSG__BUILDER_HPP_
#define ROBOT_INTERFACES__MSG__DETAIL__DETACH_MSG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_interfaces/msg/detail/detach_msg__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_interfaces
{

namespace msg
{

namespace builder
{

class Init_DetachMsg_detach_msg
{
public:
  explicit Init_DetachMsg_detach_msg(::robot_interfaces::msg::DetachMsg & msg)
  : msg_(msg)
  {}
  ::robot_interfaces::msg::DetachMsg detach_msg(::robot_interfaces::msg::DetachMsg::_detach_msg_type arg)
  {
    msg_.detach_msg = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_interfaces::msg::DetachMsg msg_;
};

class Init_DetachMsg_attach_msg
{
public:
  Init_DetachMsg_attach_msg()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DetachMsg_detach_msg attach_msg(::robot_interfaces::msg::DetachMsg::_attach_msg_type arg)
  {
    msg_.attach_msg = std::move(arg);
    return Init_DetachMsg_detach_msg(msg_);
  }

private:
  ::robot_interfaces::msg::DetachMsg msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_interfaces::msg::DetachMsg>()
{
  return robot_interfaces::msg::builder::Init_DetachMsg_attach_msg();
}

}  // namespace robot_interfaces

#endif  // ROBOT_INTERFACES__MSG__DETAIL__DETACH_MSG__BUILDER_HPP_
