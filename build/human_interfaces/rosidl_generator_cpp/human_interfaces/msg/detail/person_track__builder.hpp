// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from human_interfaces:msg/PersonTrack.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "human_interfaces/msg/person_track.hpp"


#ifndef HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACK__BUILDER_HPP_
#define HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "human_interfaces/msg/detail/person_track__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace human_interfaces
{

namespace msg
{

namespace builder
{

class Init_PersonTrack_position
{
public:
  explicit Init_PersonTrack_position(::human_interfaces::msg::PersonTrack & msg)
  : msg_(msg)
  {}
  ::human_interfaces::msg::PersonTrack position(::human_interfaces::msg::PersonTrack::_position_type arg)
  {
    msg_.position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::human_interfaces::msg::PersonTrack msg_;
};

class Init_PersonTrack_confidence
{
public:
  explicit Init_PersonTrack_confidence(::human_interfaces::msg::PersonTrack & msg)
  : msg_(msg)
  {}
  Init_PersonTrack_position confidence(::human_interfaces::msg::PersonTrack::_confidence_type arg)
  {
    msg_.confidence = std::move(arg);
    return Init_PersonTrack_position(msg_);
  }

private:
  ::human_interfaces::msg::PersonTrack msg_;
};

class Init_PersonTrack_keypoints
{
public:
  explicit Init_PersonTrack_keypoints(::human_interfaces::msg::PersonTrack & msg)
  : msg_(msg)
  {}
  Init_PersonTrack_confidence keypoints(::human_interfaces::msg::PersonTrack::_keypoints_type arg)
  {
    msg_.keypoints = std::move(arg);
    return Init_PersonTrack_confidence(msg_);
  }

private:
  ::human_interfaces::msg::PersonTrack msg_;
};

class Init_PersonTrack_id
{
public:
  Init_PersonTrack_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PersonTrack_keypoints id(::human_interfaces::msg::PersonTrack::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_PersonTrack_keypoints(msg_);
  }

private:
  ::human_interfaces::msg::PersonTrack msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::human_interfaces::msg::PersonTrack>()
{
  return human_interfaces::msg::builder::Init_PersonTrack_id();
}

}  // namespace human_interfaces

#endif  // HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACK__BUILDER_HPP_
