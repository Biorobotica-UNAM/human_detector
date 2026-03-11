// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from human_interfaces:srv/DetectPointing.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "human_interfaces/srv/detect_pointing.h"


#ifndef HUMAN_INTERFACES__SRV__DETAIL__DETECT_POINTING__STRUCT_H_
#define HUMAN_INTERFACES__SRV__DETAIL__DETECT_POINTING__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/DetectPointing in the package human_interfaces.
typedef struct human_interfaces__srv__DetectPointing_Request
{
  uint8_t structure_needs_at_least_one_member;
} human_interfaces__srv__DetectPointing_Request;

// Struct for a sequence of human_interfaces__srv__DetectPointing_Request.
typedef struct human_interfaces__srv__DetectPointing_Request__Sequence
{
  human_interfaces__srv__DetectPointing_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} human_interfaces__srv__DetectPointing_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'direction'
#include "rosidl_runtime_c/string.h"
// Member 'pose_image'
#include "sensor_msgs/msg/detail/image__struct.h"

/// Struct defined in srv/DetectPointing in the package human_interfaces.
typedef struct human_interfaces__srv__DetectPointing_Response
{
  bool human_detected;
  int32_t target_x;
  int32_t target_y;
  float target_z;
  rosidl_runtime_c__String direction;
  sensor_msgs__msg__Image pose_image;
} human_interfaces__srv__DetectPointing_Response;

// Struct for a sequence of human_interfaces__srv__DetectPointing_Response.
typedef struct human_interfaces__srv__DetectPointing_Response__Sequence
{
  human_interfaces__srv__DetectPointing_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} human_interfaces__srv__DetectPointing_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  human_interfaces__srv__DetectPointing_Event__request__MAX_SIZE = 1
};
// response
enum
{
  human_interfaces__srv__DetectPointing_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/DetectPointing in the package human_interfaces.
typedef struct human_interfaces__srv__DetectPointing_Event
{
  service_msgs__msg__ServiceEventInfo info;
  human_interfaces__srv__DetectPointing_Request__Sequence request;
  human_interfaces__srv__DetectPointing_Response__Sequence response;
} human_interfaces__srv__DetectPointing_Event;

// Struct for a sequence of human_interfaces__srv__DetectPointing_Event.
typedef struct human_interfaces__srv__DetectPointing_Event__Sequence
{
  human_interfaces__srv__DetectPointing_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} human_interfaces__srv__DetectPointing_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HUMAN_INTERFACES__SRV__DETAIL__DETECT_POINTING__STRUCT_H_
