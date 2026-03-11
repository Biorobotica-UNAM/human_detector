// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from human_interfaces:srv/ObjectDescription.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "human_interfaces/srv/object_description.hpp"


#ifndef HUMAN_INTERFACES__SRV__DETAIL__OBJECT_DESCRIPTION__BUILDER_HPP_
#define HUMAN_INTERFACES__SRV__DETAIL__OBJECT_DESCRIPTION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "human_interfaces/srv/detail/object_description__struct.hpp"
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
auto build<::human_interfaces::srv::ObjectDescription_Request>()
{
  return ::human_interfaces::srv::ObjectDescription_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace human_interfaces


namespace human_interfaces
{

namespace srv
{

namespace builder
{

class Init_ObjectDescription_Response_json_output
{
public:
  Init_ObjectDescription_Response_json_output()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::human_interfaces::srv::ObjectDescription_Response json_output(::human_interfaces::srv::ObjectDescription_Response::_json_output_type arg)
  {
    msg_.json_output = std::move(arg);
    return std::move(msg_);
  }

private:
  ::human_interfaces::srv::ObjectDescription_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::human_interfaces::srv::ObjectDescription_Response>()
{
  return human_interfaces::srv::builder::Init_ObjectDescription_Response_json_output();
}

}  // namespace human_interfaces


namespace human_interfaces
{

namespace srv
{

namespace builder
{

class Init_ObjectDescription_Event_response
{
public:
  explicit Init_ObjectDescription_Event_response(::human_interfaces::srv::ObjectDescription_Event & msg)
  : msg_(msg)
  {}
  ::human_interfaces::srv::ObjectDescription_Event response(::human_interfaces::srv::ObjectDescription_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::human_interfaces::srv::ObjectDescription_Event msg_;
};

class Init_ObjectDescription_Event_request
{
public:
  explicit Init_ObjectDescription_Event_request(::human_interfaces::srv::ObjectDescription_Event & msg)
  : msg_(msg)
  {}
  Init_ObjectDescription_Event_response request(::human_interfaces::srv::ObjectDescription_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_ObjectDescription_Event_response(msg_);
  }

private:
  ::human_interfaces::srv::ObjectDescription_Event msg_;
};

class Init_ObjectDescription_Event_info
{
public:
  Init_ObjectDescription_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ObjectDescription_Event_request info(::human_interfaces::srv::ObjectDescription_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_ObjectDescription_Event_request(msg_);
  }

private:
  ::human_interfaces::srv::ObjectDescription_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::human_interfaces::srv::ObjectDescription_Event>()
{
  return human_interfaces::srv::builder::Init_ObjectDescription_Event_info();
}

}  // namespace human_interfaces

#endif  // HUMAN_INTERFACES__SRV__DETAIL__OBJECT_DESCRIPTION__BUILDER_HPP_
