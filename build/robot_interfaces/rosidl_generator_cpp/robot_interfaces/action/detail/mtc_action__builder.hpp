// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_interfaces:action/MtcAction.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_interfaces/action/mtc_action.hpp"


#ifndef ROBOT_INTERFACES__ACTION__DETAIL__MTC_ACTION__BUILDER_HPP_
#define ROBOT_INTERFACES__ACTION__DETAIL__MTC_ACTION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_interfaces/action/detail/mtc_action__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_interfaces
{

namespace action
{

namespace builder
{

class Init_MtcAction_Goal_action
{
public:
  Init_MtcAction_Goal_action()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_interfaces::action::MtcAction_Goal action(::robot_interfaces::action::MtcAction_Goal::_action_type arg)
  {
    msg_.action = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_interfaces::action::MtcAction_Goal>()
{
  return robot_interfaces::action::builder::Init_MtcAction_Goal_action();
}

}  // namespace robot_interfaces


namespace robot_interfaces
{

namespace action
{

namespace builder
{

class Init_MtcAction_Result_success
{
public:
  explicit Init_MtcAction_Result_success(::robot_interfaces::action::MtcAction_Result & msg)
  : msg_(msg)
  {}
  ::robot_interfaces::action::MtcAction_Result success(::robot_interfaces::action::MtcAction_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_Result msg_;
};

class Init_MtcAction_Result_object_count_result
{
public:
  Init_MtcAction_Result_object_count_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MtcAction_Result_success object_count_result(::robot_interfaces::action::MtcAction_Result::_object_count_result_type arg)
  {
    msg_.object_count_result = std::move(arg);
    return Init_MtcAction_Result_success(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_interfaces::action::MtcAction_Result>()
{
  return robot_interfaces::action::builder::Init_MtcAction_Result_object_count_result();
}

}  // namespace robot_interfaces


namespace robot_interfaces
{

namespace action
{

namespace builder
{

class Init_MtcAction_Feedback_object_count_feedback
{
public:
  Init_MtcAction_Feedback_object_count_feedback()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_interfaces::action::MtcAction_Feedback object_count_feedback(::robot_interfaces::action::MtcAction_Feedback::_object_count_feedback_type arg)
  {
    msg_.object_count_feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_interfaces::action::MtcAction_Feedback>()
{
  return robot_interfaces::action::builder::Init_MtcAction_Feedback_object_count_feedback();
}

}  // namespace robot_interfaces


namespace robot_interfaces
{

namespace action
{

namespace builder
{

class Init_MtcAction_SendGoal_Request_goal
{
public:
  explicit Init_MtcAction_SendGoal_Request_goal(::robot_interfaces::action::MtcAction_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::robot_interfaces::action::MtcAction_SendGoal_Request goal(::robot_interfaces::action::MtcAction_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_SendGoal_Request msg_;
};

class Init_MtcAction_SendGoal_Request_goal_id
{
public:
  Init_MtcAction_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MtcAction_SendGoal_Request_goal goal_id(::robot_interfaces::action::MtcAction_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_MtcAction_SendGoal_Request_goal(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_interfaces::action::MtcAction_SendGoal_Request>()
{
  return robot_interfaces::action::builder::Init_MtcAction_SendGoal_Request_goal_id();
}

}  // namespace robot_interfaces


namespace robot_interfaces
{

namespace action
{

namespace builder
{

class Init_MtcAction_SendGoal_Response_stamp
{
public:
  explicit Init_MtcAction_SendGoal_Response_stamp(::robot_interfaces::action::MtcAction_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::robot_interfaces::action::MtcAction_SendGoal_Response stamp(::robot_interfaces::action::MtcAction_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_SendGoal_Response msg_;
};

class Init_MtcAction_SendGoal_Response_accepted
{
public:
  Init_MtcAction_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MtcAction_SendGoal_Response_stamp accepted(::robot_interfaces::action::MtcAction_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_MtcAction_SendGoal_Response_stamp(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_interfaces::action::MtcAction_SendGoal_Response>()
{
  return robot_interfaces::action::builder::Init_MtcAction_SendGoal_Response_accepted();
}

}  // namespace robot_interfaces


namespace robot_interfaces
{

namespace action
{

namespace builder
{

class Init_MtcAction_SendGoal_Event_response
{
public:
  explicit Init_MtcAction_SendGoal_Event_response(::robot_interfaces::action::MtcAction_SendGoal_Event & msg)
  : msg_(msg)
  {}
  ::robot_interfaces::action::MtcAction_SendGoal_Event response(::robot_interfaces::action::MtcAction_SendGoal_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_SendGoal_Event msg_;
};

class Init_MtcAction_SendGoal_Event_request
{
public:
  explicit Init_MtcAction_SendGoal_Event_request(::robot_interfaces::action::MtcAction_SendGoal_Event & msg)
  : msg_(msg)
  {}
  Init_MtcAction_SendGoal_Event_response request(::robot_interfaces::action::MtcAction_SendGoal_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_MtcAction_SendGoal_Event_response(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_SendGoal_Event msg_;
};

class Init_MtcAction_SendGoal_Event_info
{
public:
  Init_MtcAction_SendGoal_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MtcAction_SendGoal_Event_request info(::robot_interfaces::action::MtcAction_SendGoal_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_MtcAction_SendGoal_Event_request(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_SendGoal_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_interfaces::action::MtcAction_SendGoal_Event>()
{
  return robot_interfaces::action::builder::Init_MtcAction_SendGoal_Event_info();
}

}  // namespace robot_interfaces


namespace robot_interfaces
{

namespace action
{

namespace builder
{

class Init_MtcAction_GetResult_Request_goal_id
{
public:
  Init_MtcAction_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_interfaces::action::MtcAction_GetResult_Request goal_id(::robot_interfaces::action::MtcAction_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_interfaces::action::MtcAction_GetResult_Request>()
{
  return robot_interfaces::action::builder::Init_MtcAction_GetResult_Request_goal_id();
}

}  // namespace robot_interfaces


namespace robot_interfaces
{

namespace action
{

namespace builder
{

class Init_MtcAction_GetResult_Response_result
{
public:
  explicit Init_MtcAction_GetResult_Response_result(::robot_interfaces::action::MtcAction_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::robot_interfaces::action::MtcAction_GetResult_Response result(::robot_interfaces::action::MtcAction_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_GetResult_Response msg_;
};

class Init_MtcAction_GetResult_Response_status
{
public:
  Init_MtcAction_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MtcAction_GetResult_Response_result status(::robot_interfaces::action::MtcAction_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_MtcAction_GetResult_Response_result(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_interfaces::action::MtcAction_GetResult_Response>()
{
  return robot_interfaces::action::builder::Init_MtcAction_GetResult_Response_status();
}

}  // namespace robot_interfaces


namespace robot_interfaces
{

namespace action
{

namespace builder
{

class Init_MtcAction_GetResult_Event_response
{
public:
  explicit Init_MtcAction_GetResult_Event_response(::robot_interfaces::action::MtcAction_GetResult_Event & msg)
  : msg_(msg)
  {}
  ::robot_interfaces::action::MtcAction_GetResult_Event response(::robot_interfaces::action::MtcAction_GetResult_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_GetResult_Event msg_;
};

class Init_MtcAction_GetResult_Event_request
{
public:
  explicit Init_MtcAction_GetResult_Event_request(::robot_interfaces::action::MtcAction_GetResult_Event & msg)
  : msg_(msg)
  {}
  Init_MtcAction_GetResult_Event_response request(::robot_interfaces::action::MtcAction_GetResult_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_MtcAction_GetResult_Event_response(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_GetResult_Event msg_;
};

class Init_MtcAction_GetResult_Event_info
{
public:
  Init_MtcAction_GetResult_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MtcAction_GetResult_Event_request info(::robot_interfaces::action::MtcAction_GetResult_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_MtcAction_GetResult_Event_request(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_GetResult_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_interfaces::action::MtcAction_GetResult_Event>()
{
  return robot_interfaces::action::builder::Init_MtcAction_GetResult_Event_info();
}

}  // namespace robot_interfaces


namespace robot_interfaces
{

namespace action
{

namespace builder
{

class Init_MtcAction_FeedbackMessage_feedback
{
public:
  explicit Init_MtcAction_FeedbackMessage_feedback(::robot_interfaces::action::MtcAction_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::robot_interfaces::action::MtcAction_FeedbackMessage feedback(::robot_interfaces::action::MtcAction_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_FeedbackMessage msg_;
};

class Init_MtcAction_FeedbackMessage_goal_id
{
public:
  Init_MtcAction_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MtcAction_FeedbackMessage_feedback goal_id(::robot_interfaces::action::MtcAction_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_MtcAction_FeedbackMessage_feedback(msg_);
  }

private:
  ::robot_interfaces::action::MtcAction_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_interfaces::action::MtcAction_FeedbackMessage>()
{
  return robot_interfaces::action::builder::Init_MtcAction_FeedbackMessage_goal_id();
}

}  // namespace robot_interfaces

#endif  // ROBOT_INTERFACES__ACTION__DETAIL__MTC_ACTION__BUILDER_HPP_
