// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from linkattacher_msgs:srv/AttachLink.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "linkattacher_msgs/srv/attach_link.hpp"


#ifndef LINKATTACHER_MSGS__SRV__DETAIL__ATTACH_LINK__TRAITS_HPP_
#define LINKATTACHER_MSGS__SRV__DETAIL__ATTACH_LINK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "linkattacher_msgs/srv/detail/attach_link__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace linkattacher_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const AttachLink_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: model1_name
  {
    out << "model1_name: ";
    rosidl_generator_traits::value_to_yaml(msg.model1_name, out);
    out << ", ";
  }

  // member: link1_name
  {
    out << "link1_name: ";
    rosidl_generator_traits::value_to_yaml(msg.link1_name, out);
    out << ", ";
  }

  // member: model2_name
  {
    out << "model2_name: ";
    rosidl_generator_traits::value_to_yaml(msg.model2_name, out);
    out << ", ";
  }

  // member: link2_name
  {
    out << "link2_name: ";
    rosidl_generator_traits::value_to_yaml(msg.link2_name, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AttachLink_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: model1_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "model1_name: ";
    rosidl_generator_traits::value_to_yaml(msg.model1_name, out);
    out << "\n";
  }

  // member: link1_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "link1_name: ";
    rosidl_generator_traits::value_to_yaml(msg.link1_name, out);
    out << "\n";
  }

  // member: model2_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "model2_name: ";
    rosidl_generator_traits::value_to_yaml(msg.model2_name, out);
    out << "\n";
  }

  // member: link2_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "link2_name: ";
    rosidl_generator_traits::value_to_yaml(msg.link2_name, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AttachLink_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace linkattacher_msgs

namespace rosidl_generator_traits
{

[[deprecated("use linkattacher_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const linkattacher_msgs::srv::AttachLink_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  linkattacher_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use linkattacher_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const linkattacher_msgs::srv::AttachLink_Request & msg)
{
  return linkattacher_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<linkattacher_msgs::srv::AttachLink_Request>()
{
  return "linkattacher_msgs::srv::AttachLink_Request";
}

template<>
inline const char * name<linkattacher_msgs::srv::AttachLink_Request>()
{
  return "linkattacher_msgs/srv/AttachLink_Request";
}

template<>
struct has_fixed_size<linkattacher_msgs::srv::AttachLink_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<linkattacher_msgs::srv::AttachLink_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<linkattacher_msgs::srv::AttachLink_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace linkattacher_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const AttachLink_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AttachLink_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AttachLink_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace linkattacher_msgs

namespace rosidl_generator_traits
{

[[deprecated("use linkattacher_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const linkattacher_msgs::srv::AttachLink_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  linkattacher_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use linkattacher_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const linkattacher_msgs::srv::AttachLink_Response & msg)
{
  return linkattacher_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<linkattacher_msgs::srv::AttachLink_Response>()
{
  return "linkattacher_msgs::srv::AttachLink_Response";
}

template<>
inline const char * name<linkattacher_msgs::srv::AttachLink_Response>()
{
  return "linkattacher_msgs/srv/AttachLink_Response";
}

template<>
struct has_fixed_size<linkattacher_msgs::srv::AttachLink_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<linkattacher_msgs::srv::AttachLink_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<linkattacher_msgs::srv::AttachLink_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace linkattacher_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const AttachLink_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AttachLink_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AttachLink_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace linkattacher_msgs

namespace rosidl_generator_traits
{

[[deprecated("use linkattacher_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const linkattacher_msgs::srv::AttachLink_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  linkattacher_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use linkattacher_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const linkattacher_msgs::srv::AttachLink_Event & msg)
{
  return linkattacher_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<linkattacher_msgs::srv::AttachLink_Event>()
{
  return "linkattacher_msgs::srv::AttachLink_Event";
}

template<>
inline const char * name<linkattacher_msgs::srv::AttachLink_Event>()
{
  return "linkattacher_msgs/srv/AttachLink_Event";
}

template<>
struct has_fixed_size<linkattacher_msgs::srv::AttachLink_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<linkattacher_msgs::srv::AttachLink_Event>
  : std::integral_constant<bool, has_bounded_size<linkattacher_msgs::srv::AttachLink_Request>::value && has_bounded_size<linkattacher_msgs::srv::AttachLink_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<linkattacher_msgs::srv::AttachLink_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<linkattacher_msgs::srv::AttachLink>()
{
  return "linkattacher_msgs::srv::AttachLink";
}

template<>
inline const char * name<linkattacher_msgs::srv::AttachLink>()
{
  return "linkattacher_msgs/srv/AttachLink";
}

template<>
struct has_fixed_size<linkattacher_msgs::srv::AttachLink>
  : std::integral_constant<
    bool,
    has_fixed_size<linkattacher_msgs::srv::AttachLink_Request>::value &&
    has_fixed_size<linkattacher_msgs::srv::AttachLink_Response>::value
  >
{
};

template<>
struct has_bounded_size<linkattacher_msgs::srv::AttachLink>
  : std::integral_constant<
    bool,
    has_bounded_size<linkattacher_msgs::srv::AttachLink_Request>::value &&
    has_bounded_size<linkattacher_msgs::srv::AttachLink_Response>::value
  >
{
};

template<>
struct is_service<linkattacher_msgs::srv::AttachLink>
  : std::true_type
{
};

template<>
struct is_service_request<linkattacher_msgs::srv::AttachLink_Request>
  : std::true_type
{
};

template<>
struct is_service_response<linkattacher_msgs::srv::AttachLink_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // LINKATTACHER_MSGS__SRV__DETAIL__ATTACH_LINK__TRAITS_HPP_
