// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from human_interfaces:srv/DetectPointing.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "human_interfaces/srv/detect_pointing.hpp"


#ifndef HUMAN_INTERFACES__SRV__DETAIL__DETECT_POINTING__BUILDER_HPP_
#define HUMAN_INTERFACES__SRV__DETAIL__DETECT_POINTING__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "human_interfaces/srv/detail/detect_pointing__struct.hpp"
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
auto build<::human_interfaces::srv::DetectPointing_Request>()
{
  return ::human_interfaces::srv::DetectPointing_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace human_interfaces


namespace human_interfaces
{

namespace srv
{

namespace builder
{

class Init_DetectPointing_Response_pose_image
{
public:
  explicit Init_DetectPointing_Response_pose_image(::human_interfaces::srv::DetectPointing_Response & msg)
  : msg_(msg)
  {}
  ::human_interfaces::srv::DetectPointing_Response pose_image(::human_interfaces::srv::DetectPointing_Response::_pose_image_type arg)
  {
    msg_.pose_image = std::move(arg);
    return std::move(msg_);
  }

private:
  ::human_interfaces::srv::DetectPointing_Response msg_;
};

class Init_DetectPointing_Response_direction
{
public:
  explicit Init_DetectPointing_Response_direction(::human_interfaces::srv::DetectPointing_Response & msg)
  : msg_(msg)
  {}
  Init_DetectPointing_Response_pose_image direction(::human_interfaces::srv::DetectPointing_Response::_direction_type arg)
  {
    msg_.direction = std::move(arg);
    return Init_DetectPointing_Response_pose_image(msg_);
  }

private:
  ::human_interfaces::srv::DetectPointing_Response msg_;
};

class Init_DetectPointing_Response_target_z
{
public:
  explicit Init_DetectPointing_Response_target_z(::human_interfaces::srv::DetectPointing_Response & msg)
  : msg_(msg)
  {}
  Init_DetectPointing_Response_direction target_z(::human_interfaces::srv::DetectPointing_Response::_target_z_type arg)
  {
    msg_.target_z = std::move(arg);
    return Init_DetectPointing_Response_direction(msg_);
  }

private:
  ::human_interfaces::srv::DetectPointing_Response msg_;
};

class Init_DetectPointing_Response_target_y
{
public:
  explicit Init_DetectPointing_Response_target_y(::human_interfaces::srv::DetectPointing_Response & msg)
  : msg_(msg)
  {}
  Init_DetectPointing_Response_target_z target_y(::human_interfaces::srv::DetectPointing_Response::_target_y_type arg)
  {
    msg_.target_y = std::move(arg);
    return Init_DetectPointing_Response_target_z(msg_);
  }

private:
  ::human_interfaces::srv::DetectPointing_Response msg_;
};

class Init_DetectPointing_Response_target_x
{
public:
  explicit Init_DetectPointing_Response_target_x(::human_interfaces::srv::DetectPointing_Response & msg)
  : msg_(msg)
  {}
  Init_DetectPointing_Response_target_y target_x(::human_interfaces::srv::DetectPointing_Response::_target_x_type arg)
  {
    msg_.target_x = std::move(arg);
    return Init_DetectPointing_Response_target_y(msg_);
  }

private:
  ::human_interfaces::srv::DetectPointing_Response msg_;
};

class Init_DetectPointing_Response_human_detected
{
public:
  Init_DetectPointing_Response_human_detected()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DetectPointing_Response_target_x human_detected(::human_interfaces::srv::DetectPointing_Response::_human_detected_type arg)
  {
    msg_.human_detected = std::move(arg);
    return Init_DetectPointing_Response_target_x(msg_);
  }

private:
  ::human_interfaces::srv::DetectPointing_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::human_interfaces::srv::DetectPointing_Response>()
{
  return human_interfaces::srv::builder::Init_DetectPointing_Response_human_detected();
}

}  // namespace human_interfaces


namespace human_interfaces
{

namespace srv
{

namespace builder
{

class Init_DetectPointing_Event_response
{
public:
  explicit Init_DetectPointing_Event_response(::human_interfaces::srv::DetectPointing_Event & msg)
  : msg_(msg)
  {}
  ::human_interfaces::srv::DetectPointing_Event response(::human_interfaces::srv::DetectPointing_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::human_interfaces::srv::DetectPointing_Event msg_;
};

class Init_DetectPointing_Event_request
{
public:
  explicit Init_DetectPointing_Event_request(::human_interfaces::srv::DetectPointing_Event & msg)
  : msg_(msg)
  {}
  Init_DetectPointing_Event_response request(::human_interfaces::srv::DetectPointing_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_DetectPointing_Event_response(msg_);
  }

private:
  ::human_interfaces::srv::DetectPointing_Event msg_;
};

class Init_DetectPointing_Event_info
{
public:
  Init_DetectPointing_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DetectPointing_Event_request info(::human_interfaces::srv::DetectPointing_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_DetectPointing_Event_request(msg_);
  }

private:
  ::human_interfaces::srv::DetectPointing_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::human_interfaces::srv::DetectPointing_Event>()
{
  return human_interfaces::srv::builder::Init_DetectPointing_Event_info();
}

}  // namespace human_interfaces

#endif  // HUMAN_INTERFACES__SRV__DETAIL__DETECT_POINTING__BUILDER_HPP_
