// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from human_interfaces:msg/PersonTracks.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "human_interfaces/msg/person_tracks.hpp"


#ifndef HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACKS__BUILDER_HPP_
#define HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACKS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "human_interfaces/msg/detail/person_tracks__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace human_interfaces
{

namespace msg
{

namespace builder
{

class Init_PersonTracks_persons
{
public:
  explicit Init_PersonTracks_persons(::human_interfaces::msg::PersonTracks & msg)
  : msg_(msg)
  {}
  ::human_interfaces::msg::PersonTracks persons(::human_interfaces::msg::PersonTracks::_persons_type arg)
  {
    msg_.persons = std::move(arg);
    return std::move(msg_);
  }

private:
  ::human_interfaces::msg::PersonTracks msg_;
};

class Init_PersonTracks_header
{
public:
  Init_PersonTracks_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PersonTracks_persons header(::human_interfaces::msg::PersonTracks::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_PersonTracks_persons(msg_);
  }

private:
  ::human_interfaces::msg::PersonTracks msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::human_interfaces::msg::PersonTracks>()
{
  return human_interfaces::msg::builder::Init_PersonTracks_header();
}

}  // namespace human_interfaces

#endif  // HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACKS__BUILDER_HPP_
