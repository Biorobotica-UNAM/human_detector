// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from human_interfaces:srv/DetectPointing.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "human_interfaces/srv/detect_pointing.hpp"


#ifndef HUMAN_INTERFACES__SRV__DETAIL__DETECT_POINTING__TRAITS_HPP_
#define HUMAN_INTERFACES__SRV__DETAIL__DETECT_POINTING__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "human_interfaces/srv/detail/detect_pointing__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace human_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const DetectPointing_Request & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DetectPointing_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DetectPointing_Request & msg, bool use_flow_style = false)
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

}  // namespace human_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use human_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const human_interfaces::srv::DetectPointing_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  human_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use human_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const human_interfaces::srv::DetectPointing_Request & msg)
{
  return human_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<human_interfaces::srv::DetectPointing_Request>()
{
  return "human_interfaces::srv::DetectPointing_Request";
}

template<>
inline const char * name<human_interfaces::srv::DetectPointing_Request>()
{
  return "human_interfaces/srv/DetectPointing_Request";
}

template<>
struct has_fixed_size<human_interfaces::srv::DetectPointing_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<human_interfaces::srv::DetectPointing_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<human_interfaces::srv::DetectPointing_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'pose_image'
#include "sensor_msgs/msg/detail/image__traits.hpp"

namespace human_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const DetectPointing_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: human_detected
  {
    out << "human_detected: ";
    rosidl_generator_traits::value_to_yaml(msg.human_detected, out);
    out << ", ";
  }

  // member: target_x
  {
    out << "target_x: ";
    rosidl_generator_traits::value_to_yaml(msg.target_x, out);
    out << ", ";
  }

  // member: target_y
  {
    out << "target_y: ";
    rosidl_generator_traits::value_to_yaml(msg.target_y, out);
    out << ", ";
  }

  // member: target_z
  {
    out << "target_z: ";
    rosidl_generator_traits::value_to_yaml(msg.target_z, out);
    out << ", ";
  }

  // member: direction
  {
    out << "direction: ";
    rosidl_generator_traits::value_to_yaml(msg.direction, out);
    out << ", ";
  }

  // member: pose_image
  {
    out << "pose_image: ";
    to_flow_style_yaml(msg.pose_image, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DetectPointing_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: human_detected
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "human_detected: ";
    rosidl_generator_traits::value_to_yaml(msg.human_detected, out);
    out << "\n";
  }

  // member: target_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_x: ";
    rosidl_generator_traits::value_to_yaml(msg.target_x, out);
    out << "\n";
  }

  // member: target_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_y: ";
    rosidl_generator_traits::value_to_yaml(msg.target_y, out);
    out << "\n";
  }

  // member: target_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_z: ";
    rosidl_generator_traits::value_to_yaml(msg.target_z, out);
    out << "\n";
  }

  // member: direction
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "direction: ";
    rosidl_generator_traits::value_to_yaml(msg.direction, out);
    out << "\n";
  }

  // member: pose_image
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose_image:\n";
    to_block_style_yaml(msg.pose_image, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DetectPointing_Response & msg, bool use_flow_style = false)
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

}  // namespace human_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use human_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const human_interfaces::srv::DetectPointing_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  human_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use human_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const human_interfaces::srv::DetectPointing_Response & msg)
{
  return human_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<human_interfaces::srv::DetectPointing_Response>()
{
  return "human_interfaces::srv::DetectPointing_Response";
}

template<>
inline const char * name<human_interfaces::srv::DetectPointing_Response>()
{
  return "human_interfaces/srv/DetectPointing_Response";
}

template<>
struct has_fixed_size<human_interfaces::srv::DetectPointing_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<human_interfaces::srv::DetectPointing_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<human_interfaces::srv::DetectPointing_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace human_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const DetectPointing_Event & msg,
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
  const DetectPointing_Event & msg,
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

inline std::string to_yaml(const DetectPointing_Event & msg, bool use_flow_style = false)
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

}  // namespace human_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use human_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const human_interfaces::srv::DetectPointing_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  human_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use human_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const human_interfaces::srv::DetectPointing_Event & msg)
{
  return human_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<human_interfaces::srv::DetectPointing_Event>()
{
  return "human_interfaces::srv::DetectPointing_Event";
}

template<>
inline const char * name<human_interfaces::srv::DetectPointing_Event>()
{
  return "human_interfaces/srv/DetectPointing_Event";
}

template<>
struct has_fixed_size<human_interfaces::srv::DetectPointing_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<human_interfaces::srv::DetectPointing_Event>
  : std::integral_constant<bool, has_bounded_size<human_interfaces::srv::DetectPointing_Request>::value && has_bounded_size<human_interfaces::srv::DetectPointing_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<human_interfaces::srv::DetectPointing_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<human_interfaces::srv::DetectPointing>()
{
  return "human_interfaces::srv::DetectPointing";
}

template<>
inline const char * name<human_interfaces::srv::DetectPointing>()
{
  return "human_interfaces/srv/DetectPointing";
}

template<>
struct has_fixed_size<human_interfaces::srv::DetectPointing>
  : std::integral_constant<
    bool,
    has_fixed_size<human_interfaces::srv::DetectPointing_Request>::value &&
    has_fixed_size<human_interfaces::srv::DetectPointing_Response>::value
  >
{
};

template<>
struct has_bounded_size<human_interfaces::srv::DetectPointing>
  : std::integral_constant<
    bool,
    has_bounded_size<human_interfaces::srv::DetectPointing_Request>::value &&
    has_bounded_size<human_interfaces::srv::DetectPointing_Response>::value
  >
{
};

template<>
struct is_service<human_interfaces::srv::DetectPointing>
  : std::true_type
{
};

template<>
struct is_service_request<human_interfaces::srv::DetectPointing_Request>
  : std::true_type
{
};

template<>
struct is_service_response<human_interfaces::srv::DetectPointing_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // HUMAN_INTERFACES__SRV__DETAIL__DETECT_POINTING__TRAITS_HPP_
