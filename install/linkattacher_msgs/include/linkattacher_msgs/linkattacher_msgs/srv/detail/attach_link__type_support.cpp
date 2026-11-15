// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from linkattacher_msgs:srv/AttachLink.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "linkattacher_msgs/srv/detail/attach_link__functions.h"
#include "linkattacher_msgs/srv/detail/attach_link__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace linkattacher_msgs
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void AttachLink_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) linkattacher_msgs::srv::AttachLink_Request(_init);
}

void AttachLink_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<linkattacher_msgs::srv::AttachLink_Request *>(message_memory);
  typed_message->~AttachLink_Request();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember AttachLink_Request_message_member_array[4] = {
  {
    "model1_name",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(linkattacher_msgs::srv::AttachLink_Request, model1_name),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "link1_name",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(linkattacher_msgs::srv::AttachLink_Request, link1_name),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "model2_name",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(linkattacher_msgs::srv::AttachLink_Request, model2_name),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "link2_name",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(linkattacher_msgs::srv::AttachLink_Request, link2_name),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers AttachLink_Request_message_members = {
  "linkattacher_msgs::srv",  // message namespace
  "AttachLink_Request",  // message name
  4,  // number of fields
  sizeof(linkattacher_msgs::srv::AttachLink_Request),
  false,  // has_any_key_member_
  AttachLink_Request_message_member_array,  // message members
  AttachLink_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  AttachLink_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t AttachLink_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &AttachLink_Request_message_members,
  get_message_typesupport_handle_function,
  &linkattacher_msgs__srv__AttachLink_Request__get_type_hash,
  &linkattacher_msgs__srv__AttachLink_Request__get_type_description,
  &linkattacher_msgs__srv__AttachLink_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace linkattacher_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<linkattacher_msgs::srv::AttachLink_Request>()
{
  return &::linkattacher_msgs::srv::rosidl_typesupport_introspection_cpp::AttachLink_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, linkattacher_msgs, srv, AttachLink_Request)() {
  return &::linkattacher_msgs::srv::rosidl_typesupport_introspection_cpp::AttachLink_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "linkattacher_msgs/srv/detail/attach_link__functions.h"
// already included above
// #include "linkattacher_msgs/srv/detail/attach_link__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace linkattacher_msgs
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void AttachLink_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) linkattacher_msgs::srv::AttachLink_Response(_init);
}

void AttachLink_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<linkattacher_msgs::srv::AttachLink_Response *>(message_memory);
  typed_message->~AttachLink_Response();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember AttachLink_Response_message_member_array[2] = {
  {
    "success",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(linkattacher_msgs::srv::AttachLink_Response, success),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "message",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(linkattacher_msgs::srv::AttachLink_Response, message),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers AttachLink_Response_message_members = {
  "linkattacher_msgs::srv",  // message namespace
  "AttachLink_Response",  // message name
  2,  // number of fields
  sizeof(linkattacher_msgs::srv::AttachLink_Response),
  false,  // has_any_key_member_
  AttachLink_Response_message_member_array,  // message members
  AttachLink_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  AttachLink_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t AttachLink_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &AttachLink_Response_message_members,
  get_message_typesupport_handle_function,
  &linkattacher_msgs__srv__AttachLink_Response__get_type_hash,
  &linkattacher_msgs__srv__AttachLink_Response__get_type_description,
  &linkattacher_msgs__srv__AttachLink_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace linkattacher_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<linkattacher_msgs::srv::AttachLink_Response>()
{
  return &::linkattacher_msgs::srv::rosidl_typesupport_introspection_cpp::AttachLink_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, linkattacher_msgs, srv, AttachLink_Response)() {
  return &::linkattacher_msgs::srv::rosidl_typesupport_introspection_cpp::AttachLink_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "linkattacher_msgs/srv/detail/attach_link__functions.h"
// already included above
// #include "linkattacher_msgs/srv/detail/attach_link__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace linkattacher_msgs
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void AttachLink_Event_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) linkattacher_msgs::srv::AttachLink_Event(_init);
}

void AttachLink_Event_fini_function(void * message_memory)
{
  auto typed_message = static_cast<linkattacher_msgs::srv::AttachLink_Event *>(message_memory);
  typed_message->~AttachLink_Event();
}

size_t size_function__AttachLink_Event__request(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<linkattacher_msgs::srv::AttachLink_Request> *>(untyped_member);
  return member->size();
}

const void * get_const_function__AttachLink_Event__request(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<linkattacher_msgs::srv::AttachLink_Request> *>(untyped_member);
  return &member[index];
}

void * get_function__AttachLink_Event__request(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<linkattacher_msgs::srv::AttachLink_Request> *>(untyped_member);
  return &member[index];
}

void fetch_function__AttachLink_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const linkattacher_msgs::srv::AttachLink_Request *>(
    get_const_function__AttachLink_Event__request(untyped_member, index));
  auto & value = *reinterpret_cast<linkattacher_msgs::srv::AttachLink_Request *>(untyped_value);
  value = item;
}

void assign_function__AttachLink_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<linkattacher_msgs::srv::AttachLink_Request *>(
    get_function__AttachLink_Event__request(untyped_member, index));
  const auto & value = *reinterpret_cast<const linkattacher_msgs::srv::AttachLink_Request *>(untyped_value);
  item = value;
}

void resize_function__AttachLink_Event__request(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<linkattacher_msgs::srv::AttachLink_Request> *>(untyped_member);
  member->resize(size);
}

size_t size_function__AttachLink_Event__response(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<linkattacher_msgs::srv::AttachLink_Response> *>(untyped_member);
  return member->size();
}

const void * get_const_function__AttachLink_Event__response(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<linkattacher_msgs::srv::AttachLink_Response> *>(untyped_member);
  return &member[index];
}

void * get_function__AttachLink_Event__response(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<linkattacher_msgs::srv::AttachLink_Response> *>(untyped_member);
  return &member[index];
}

void fetch_function__AttachLink_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const linkattacher_msgs::srv::AttachLink_Response *>(
    get_const_function__AttachLink_Event__response(untyped_member, index));
  auto & value = *reinterpret_cast<linkattacher_msgs::srv::AttachLink_Response *>(untyped_value);
  value = item;
}

void assign_function__AttachLink_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<linkattacher_msgs::srv::AttachLink_Response *>(
    get_function__AttachLink_Event__response(untyped_member, index));
  const auto & value = *reinterpret_cast<const linkattacher_msgs::srv::AttachLink_Response *>(untyped_value);
  item = value;
}

void resize_function__AttachLink_Event__response(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<linkattacher_msgs::srv::AttachLink_Response> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember AttachLink_Event_message_member_array[3] = {
  {
    "info",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<service_msgs::msg::ServiceEventInfo>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(linkattacher_msgs::srv::AttachLink_Event, info),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "request",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<linkattacher_msgs::srv::AttachLink_Request>(),  // members of sub message
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(linkattacher_msgs::srv::AttachLink_Event, request),  // bytes offset in struct
    nullptr,  // default value
    size_function__AttachLink_Event__request,  // size() function pointer
    get_const_function__AttachLink_Event__request,  // get_const(index) function pointer
    get_function__AttachLink_Event__request,  // get(index) function pointer
    fetch_function__AttachLink_Event__request,  // fetch(index, &value) function pointer
    assign_function__AttachLink_Event__request,  // assign(index, value) function pointer
    resize_function__AttachLink_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<linkattacher_msgs::srv::AttachLink_Response>(),  // members of sub message
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(linkattacher_msgs::srv::AttachLink_Event, response),  // bytes offset in struct
    nullptr,  // default value
    size_function__AttachLink_Event__response,  // size() function pointer
    get_const_function__AttachLink_Event__response,  // get_const(index) function pointer
    get_function__AttachLink_Event__response,  // get(index) function pointer
    fetch_function__AttachLink_Event__response,  // fetch(index, &value) function pointer
    assign_function__AttachLink_Event__response,  // assign(index, value) function pointer
    resize_function__AttachLink_Event__response  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers AttachLink_Event_message_members = {
  "linkattacher_msgs::srv",  // message namespace
  "AttachLink_Event",  // message name
  3,  // number of fields
  sizeof(linkattacher_msgs::srv::AttachLink_Event),
  false,  // has_any_key_member_
  AttachLink_Event_message_member_array,  // message members
  AttachLink_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  AttachLink_Event_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t AttachLink_Event_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &AttachLink_Event_message_members,
  get_message_typesupport_handle_function,
  &linkattacher_msgs__srv__AttachLink_Event__get_type_hash,
  &linkattacher_msgs__srv__AttachLink_Event__get_type_description,
  &linkattacher_msgs__srv__AttachLink_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace linkattacher_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<linkattacher_msgs::srv::AttachLink_Event>()
{
  return &::linkattacher_msgs::srv::rosidl_typesupport_introspection_cpp::AttachLink_Event_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, linkattacher_msgs, srv, AttachLink_Event)() {
  return &::linkattacher_msgs::srv::rosidl_typesupport_introspection_cpp::AttachLink_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"
// already included above
// #include "linkattacher_msgs/srv/detail/attach_link__functions.h"
// already included above
// #include "linkattacher_msgs/srv/detail/attach_link__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace linkattacher_msgs
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers AttachLink_service_members = {
  "linkattacher_msgs::srv",  // service namespace
  "AttachLink",  // service name
  // the following fields are initialized below on first access
  // see get_service_type_support_handle<linkattacher_msgs::srv::AttachLink>()
  nullptr,  // request message
  nullptr,  // response message
  nullptr,  // event message
};

static const rosidl_service_type_support_t AttachLink_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &AttachLink_service_members,
  get_service_typesupport_handle_function,
  ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<linkattacher_msgs::srv::AttachLink_Request>(),
  ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<linkattacher_msgs::srv::AttachLink_Response>(),
  ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<linkattacher_msgs::srv::AttachLink_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<linkattacher_msgs::srv::AttachLink>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<linkattacher_msgs::srv::AttachLink>,
  &linkattacher_msgs__srv__AttachLink__get_type_hash,
  &linkattacher_msgs__srv__AttachLink__get_type_description,
  &linkattacher_msgs__srv__AttachLink__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace linkattacher_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<linkattacher_msgs::srv::AttachLink>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::linkattacher_msgs::srv::rosidl_typesupport_introspection_cpp::AttachLink_service_type_support_handle;
  // get a non-const and properly typed version of the data void *
  auto service_members = const_cast<::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
    static_cast<const ::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
      service_type_support->data));
  // make sure all of the service_members are initialized
  // if they are not, initialize them
  if (
    service_members->request_members_ == nullptr ||
    service_members->response_members_ == nullptr ||
    service_members->event_members_ == nullptr)
  {
    // initialize the request_members_ with the static function from the external library
    service_members->request_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::linkattacher_msgs::srv::AttachLink_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::linkattacher_msgs::srv::AttachLink_Response
      >()->data
      );
    // initialize the event_members_ with the static function from the external library
    service_members->event_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::linkattacher_msgs::srv::AttachLink_Event
      >()->data
      );
  }
  // finally return the properly initialized service_type_support handle
  return service_type_support;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, linkattacher_msgs, srv, AttachLink)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<linkattacher_msgs::srv::AttachLink>();
}

#ifdef __cplusplus
}
#endif
