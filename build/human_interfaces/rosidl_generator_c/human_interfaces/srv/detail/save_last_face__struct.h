// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from human_interfaces:srv/SaveLastFace.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "human_interfaces/srv/save_last_face.h"


#ifndef HUMAN_INTERFACES__SRV__DETAIL__SAVE_LAST_FACE__STRUCT_H_
#define HUMAN_INTERFACES__SRV__DETAIL__SAVE_LAST_FACE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/SaveLastFace in the package human_interfaces.
typedef struct human_interfaces__srv__SaveLastFace_Request
{
  uint8_t structure_needs_at_least_one_member;
} human_interfaces__srv__SaveLastFace_Request;

// Struct for a sequence of human_interfaces__srv__SaveLastFace_Request.
typedef struct human_interfaces__srv__SaveLastFace_Request__Sequence
{
  human_interfaces__srv__SaveLastFace_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} human_interfaces__srv__SaveLastFace_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SaveLastFace in the package human_interfaces.
typedef struct human_interfaces__srv__SaveLastFace_Response
{
  bool success;
  rosidl_runtime_c__String message;
} human_interfaces__srv__SaveLastFace_Response;

// Struct for a sequence of human_interfaces__srv__SaveLastFace_Response.
typedef struct human_interfaces__srv__SaveLastFace_Response__Sequence
{
  human_interfaces__srv__SaveLastFace_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} human_interfaces__srv__SaveLastFace_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  human_interfaces__srv__SaveLastFace_Event__request__MAX_SIZE = 1
};
// response
enum
{
  human_interfaces__srv__SaveLastFace_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/SaveLastFace in the package human_interfaces.
typedef struct human_interfaces__srv__SaveLastFace_Event
{
  service_msgs__msg__ServiceEventInfo info;
  human_interfaces__srv__SaveLastFace_Request__Sequence request;
  human_interfaces__srv__SaveLastFace_Response__Sequence response;
} human_interfaces__srv__SaveLastFace_Event;

// Struct for a sequence of human_interfaces__srv__SaveLastFace_Event.
typedef struct human_interfaces__srv__SaveLastFace_Event__Sequence
{
  human_interfaces__srv__SaveLastFace_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} human_interfaces__srv__SaveLastFace_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HUMAN_INTERFACES__SRV__DETAIL__SAVE_LAST_FACE__STRUCT_H_
