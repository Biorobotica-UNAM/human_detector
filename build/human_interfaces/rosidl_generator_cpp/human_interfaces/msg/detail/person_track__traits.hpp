// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from human_interfaces:msg/PersonTrack.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "human_interfaces/msg/person_track.hpp"


#ifndef HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACK__TRAITS_HPP_
#define HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "human_interfaces/msg/detail/person_track__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace human_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const PersonTrack & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: keypoints
  {
    if (msg.keypoints.size() == 0) {
      out << "keypoints: []";
    } else {
      out << "keypoints: [";
      size_t pending_items = msg.keypoints.size();
      for (auto item : msg.keypoints) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: confidence
  {
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << ", ";
  }

  // member: position
  {
    if (msg.position.size() == 0) {
      out << "position: []";
    } else {
      out << "position: [";
      size_t pending_items = msg.position.size();
      for (auto item : msg.position) {
        rosidl_generator_traits::value_to_yaml(item, out);
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
  const PersonTrack & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: keypoints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.keypoints.size() == 0) {
      out << "keypoints: []\n";
    } else {
      out << "keypoints:\n";
      for (auto item : msg.keypoints) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: confidence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << "\n";
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.position.size() == 0) {
      out << "position: []\n";
    } else {
      out << "position:\n";
      for (auto item : msg.position) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PersonTrack & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace human_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use human_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const human_interfaces::msg::PersonTrack & msg,
  std::ostream & out, size_t indentation = 0)
{
  human_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use human_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const human_interfaces::msg::PersonTrack & msg)
{
  return human_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<human_interfaces::msg::PersonTrack>()
{
  return "human_interfaces::msg::PersonTrack";
}

template<>
inline const char * name<human_interfaces::msg::PersonTrack>()
{
  return "human_interfaces/msg/PersonTrack";
}

template<>
struct has_fixed_size<human_interfaces::msg::PersonTrack>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<human_interfaces::msg::PersonTrack>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<human_interfaces::msg::PersonTrack>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACK__TRAITS_HPP_
