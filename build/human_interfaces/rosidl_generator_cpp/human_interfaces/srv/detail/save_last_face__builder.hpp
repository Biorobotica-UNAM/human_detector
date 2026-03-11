// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from human_interfaces:srv/SaveLastFace.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "human_interfaces/srv/save_last_face.hpp"


#ifndef HUMAN_INTERFACES__SRV__DETAIL__SAVE_LAST_FACE__BUILDER_HPP_
#define HUMAN_INTERFACES__SRV__DETAIL__SAVE_LAST_FACE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "human_interfaces/srv/detail/save_last_face__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace human_interfaces
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::human_interfaces::srv::SaveLastFace_Request>()
{
  return ::human_interfaces::srv::SaveLastFace_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace human_interfaces


namespace human_interfaces
{

namespace srv
{

namespace builder
{

class Init_SaveLastFace_Response_message
{
public:
  explicit Init_SaveLastFace_Response_message(::human_interfaces::srv::SaveLastFace_Response & msg)
  : msg_(msg)
  {}
  ::human_interfaces::srv::SaveLastFace_Response message(::human_interfaces::srv::SaveLastFace_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::human_interfaces::srv::SaveLastFace_Response msg_;
};

class Init_SaveLastFace_Response_success
{
public:
  Init_SaveLastFace_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SaveLastFace_Response_message success(::human_interfaces::srv::SaveLastFace_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SaveLastFace_Response_message(msg_);
  }

private:
  ::human_interfaces::srv::SaveLastFace_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::human_interfaces::srv::SaveLastFace_Response>()
{
  return human_interfaces::srv::builder::Init_SaveLastFace_Response_success();
}

}  // namespace human_interfaces


namespace human_interfaces
{

namespace srv
{

namespace builder
{

class Init_SaveLastFace_Event_response
{
public:
  explicit Init_SaveLastFace_Event_response(::human_interfaces::srv::SaveLastFace_Event & msg)
  : msg_(msg)
  {}
  ::human_interfaces::srv::SaveLastFace_Event response(::human_interfaces::srv::SaveLastFace_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::human_interfaces::srv::SaveLastFace_Event msg_;
};

class Init_SaveLastFace_Event_request
{
public:
  explicit Init_SaveLastFace_Event_request(::human_interfaces::srv::SaveLastFace_Event & msg)
  : msg_(msg)
  {}
  Init_SaveLastFace_Event_response request(::human_interfaces::srv::SaveLastFace_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_SaveLastFace_Event_response(msg_);
  }

private:
  ::human_interfaces::srv::SaveLastFace_Event msg_;
};

class Init_SaveLastFace_Event_info
{
public:
  Init_SaveLastFace_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SaveLastFace_Event_request info(::human_interfaces::srv::SaveLastFace_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_SaveLastFace_Event_request(msg_);
  }

private:
  ::human_interfaces::srv::SaveLastFace_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::human_interfaces::srv::SaveLastFace_Event>()
{
  return human_interfaces::srv::builder::Init_SaveLastFace_Event_info();
}

}  // namespace human_interfaces

#endif  // HUMAN_INTERFACES__SRV__DETAIL__SAVE_LAST_FACE__BUILDER_HPP_
