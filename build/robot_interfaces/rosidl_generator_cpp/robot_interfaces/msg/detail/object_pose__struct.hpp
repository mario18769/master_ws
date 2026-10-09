// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_interfaces:msg/ObjectPose.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_interfaces/msg/object_pose.hpp"


#ifndef ROBOT_INTERFACES__MSG__DETAIL__OBJECT_POSE__STRUCT_HPP_
#define ROBOT_INTERFACES__MSG__DETAIL__OBJECT_POSE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robot_interfaces__msg__ObjectPose __attribute__((deprecated))
#else
# define DEPRECATED__robot_interfaces__msg__ObjectPose __declspec(deprecated)
#endif

namespace robot_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ObjectPose_
{
  using Type = ObjectPose_<ContainerAllocator>;

  explicit ObjectPose_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->object_type = "";
      this->axis_x = 0.0;
      this->axis_y = 0.0;
      this->axis_z = 0.0;
      this->axis_pt_x = 0.0;
      this->axis_pt_y = 0.0;
      this->axis_pt_z = 0.0;
      this->axis2_x = 0.0;
      this->axis2_y = 0.0;
      this->axis2_z = 0.0;
      this->radius = 0.0;
      this->length = 0.0;
      this->mid_x = 0.0;
      this->mid_y = 0.0;
      this->mid_z = 0.0;
    }
  }

  explicit ObjectPose_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : object_type(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->object_type = "";
      this->axis_x = 0.0;
      this->axis_y = 0.0;
      this->axis_z = 0.0;
      this->axis_pt_x = 0.0;
      this->axis_pt_y = 0.0;
      this->axis_pt_z = 0.0;
      this->axis2_x = 0.0;
      this->axis2_y = 0.0;
      this->axis2_z = 0.0;
      this->radius = 0.0;
      this->length = 0.0;
      this->mid_x = 0.0;
      this->mid_y = 0.0;
      this->mid_z = 0.0;
    }
  }

  // field types and members
  using _object_type_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _object_type_type object_type;
  using _axis_x_type =
    double;
  _axis_x_type axis_x;
  using _axis_y_type =
    double;
  _axis_y_type axis_y;
  using _axis_z_type =
    double;
  _axis_z_type axis_z;
  using _axis_pt_x_type =
    double;
  _axis_pt_x_type axis_pt_x;
  using _axis_pt_y_type =
    double;
  _axis_pt_y_type axis_pt_y;
  using _axis_pt_z_type =
    double;
  _axis_pt_z_type axis_pt_z;
  using _axis2_x_type =
    double;
  _axis2_x_type axis2_x;
  using _axis2_y_type =
    double;
  _axis2_y_type axis2_y;
  using _axis2_z_type =
    double;
  _axis2_z_type axis2_z;
  using _radius_type =
    double;
  _radius_type radius;
  using _length_type =
    double;
  _length_type length;
  using _mid_x_type =
    double;
  _mid_x_type mid_x;
  using _mid_y_type =
    double;
  _mid_y_type mid_y;
  using _mid_z_type =
    double;
  _mid_z_type mid_z;

  // setters for named parameter idiom
  Type & set__object_type(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->object_type = _arg;
    return *this;
  }
  Type & set__axis_x(
    const double & _arg)
  {
    this->axis_x = _arg;
    return *this;
  }
  Type & set__axis_y(
    const double & _arg)
  {
    this->axis_y = _arg;
    return *this;
  }
  Type & set__axis_z(
    const double & _arg)
  {
    this->axis_z = _arg;
    return *this;
  }
  Type & set__axis_pt_x(
    const double & _arg)
  {
    this->axis_pt_x = _arg;
    return *this;
  }
  Type & set__axis_pt_y(
    const double & _arg)
  {
    this->axis_pt_y = _arg;
    return *this;
  }
  Type & set__axis_pt_z(
    const double & _arg)
  {
    this->axis_pt_z = _arg;
    return *this;
  }
  Type & set__axis2_x(
    const double & _arg)
  {
    this->axis2_x = _arg;
    return *this;
  }
  Type & set__axis2_y(
    const double & _arg)
  {
    this->axis2_y = _arg;
    return *this;
  }
  Type & set__axis2_z(
    const double & _arg)
  {
    this->axis2_z = _arg;
    return *this;
  }
  Type & set__radius(
    const double & _arg)
  {
    this->radius = _arg;
    return *this;
  }
  Type & set__length(
    const double & _arg)
  {
    this->length = _arg;
    return *this;
  }
  Type & set__mid_x(
    const double & _arg)
  {
    this->mid_x = _arg;
    return *this;
  }
  Type & set__mid_y(
    const double & _arg)
  {
    this->mid_y = _arg;
    return *this;
  }
  Type & set__mid_z(
    const double & _arg)
  {
    this->mid_z = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_interfaces::msg::ObjectPose_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_interfaces::msg::ObjectPose_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_interfaces::msg::ObjectPose_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_interfaces::msg::ObjectPose_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_interfaces::msg::ObjectPose_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_interfaces::msg::ObjectPose_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_interfaces::msg::ObjectPose_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_interfaces::msg::ObjectPose_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_interfaces::msg::ObjectPose_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_interfaces::msg::ObjectPose_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_interfaces__msg__ObjectPose
    std::shared_ptr<robot_interfaces::msg::ObjectPose_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_interfaces__msg__ObjectPose
    std::shared_ptr<robot_interfaces::msg::ObjectPose_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ObjectPose_ & other) const
  {
    if (this->object_type != other.object_type) {
      return false;
    }
    if (this->axis_x != other.axis_x) {
      return false;
    }
    if (this->axis_y != other.axis_y) {
      return false;
    }
    if (this->axis_z != other.axis_z) {
      return false;
    }
    if (this->axis_pt_x != other.axis_pt_x) {
      return false;
    }
    if (this->axis_pt_y != other.axis_pt_y) {
      return false;
    }
    if (this->axis_pt_z != other.axis_pt_z) {
      return false;
    }
    if (this->axis2_x != other.axis2_x) {
      return false;
    }
    if (this->axis2_y != other.axis2_y) {
      return false;
    }
    if (this->axis2_z != other.axis2_z) {
      return false;
    }
    if (this->radius != other.radius) {
      return false;
    }
    if (this->length != other.length) {
      return false;
    }
    if (this->mid_x != other.mid_x) {
      return false;
    }
    if (this->mid_y != other.mid_y) {
      return false;
    }
    if (this->mid_z != other.mid_z) {
      return false;
    }
    return true;
  }
  bool operator!=(const ObjectPose_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ObjectPose_

// alias to use template instance with default allocator
using ObjectPose =
  robot_interfaces::msg::ObjectPose_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robot_interfaces

#endif  // ROBOT_INTERFACES__MSG__DETAIL__OBJECT_POSE__STRUCT_HPP_
