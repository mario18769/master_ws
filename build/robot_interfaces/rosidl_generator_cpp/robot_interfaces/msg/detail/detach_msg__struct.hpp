// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_interfaces:msg/DetachMsg.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_interfaces/msg/detach_msg.hpp"


#ifndef ROBOT_INTERFACES__MSG__DETAIL__DETACH_MSG__STRUCT_HPP_
#define ROBOT_INTERFACES__MSG__DETAIL__DETACH_MSG__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robot_interfaces__msg__DetachMsg __attribute__((deprecated))
#else
# define DEPRECATED__robot_interfaces__msg__DetachMsg __declspec(deprecated)
#endif

namespace robot_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DetachMsg_
{
  using Type = DetachMsg_<ContainerAllocator>;

  explicit DetachMsg_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->attach_msg = "";
      this->detach_msg = "";
    }
  }

  explicit DetachMsg_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : attach_msg(_alloc),
    detach_msg(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->attach_msg = "";
      this->detach_msg = "";
    }
  }

  // field types and members
  using _attach_msg_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _attach_msg_type attach_msg;
  using _detach_msg_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _detach_msg_type detach_msg;

  // setters for named parameter idiom
  Type & set__attach_msg(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->attach_msg = _arg;
    return *this;
  }
  Type & set__detach_msg(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->detach_msg = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_interfaces::msg::DetachMsg_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_interfaces::msg::DetachMsg_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_interfaces::msg::DetachMsg_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_interfaces::msg::DetachMsg_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_interfaces::msg::DetachMsg_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_interfaces::msg::DetachMsg_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_interfaces::msg::DetachMsg_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_interfaces::msg::DetachMsg_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_interfaces::msg::DetachMsg_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_interfaces::msg::DetachMsg_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_interfaces__msg__DetachMsg
    std::shared_ptr<robot_interfaces::msg::DetachMsg_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_interfaces__msg__DetachMsg
    std::shared_ptr<robot_interfaces::msg::DetachMsg_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DetachMsg_ & other) const
  {
    if (this->attach_msg != other.attach_msg) {
      return false;
    }
    if (this->detach_msg != other.detach_msg) {
      return false;
    }
    return true;
  }
  bool operator!=(const DetachMsg_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DetachMsg_

// alias to use template instance with default allocator
using DetachMsg =
  robot_interfaces::msg::DetachMsg_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robot_interfaces

#endif  // ROBOT_INTERFACES__MSG__DETAIL__DETACH_MSG__STRUCT_HPP_
