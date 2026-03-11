// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from human_interfaces:srv/DetectPointing.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "human_interfaces/srv/detail/detect_pointing__struct.h"
#include "human_interfaces/srv/detail/detect_pointing__type_support.h"
#include "human_interfaces/srv/detail/detect_pointing__functions.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace human_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _DetectPointing_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _DetectPointing_Request_type_support_ids_t;

static const _DetectPointing_Request_type_support_ids_t _DetectPointing_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _DetectPointing_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _DetectPointing_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _DetectPointing_Request_type_support_symbol_names_t _DetectPointing_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, human_interfaces, srv, DetectPointing_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, human_interfaces, srv, DetectPointing_Request)),
  }
};

typedef struct _DetectPointing_Request_type_support_data_t
{
  void * data[2];
} _DetectPointing_Request_type_support_data_t;

static _DetectPointing_Request_type_support_data_t _DetectPointing_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _DetectPointing_Request_message_typesupport_map = {
  2,
  "human_interfaces",
  &_DetectPointing_Request_message_typesupport_ids.typesupport_identifier[0],
  &_DetectPointing_Request_message_typesupport_symbol_names.symbol_name[0],
  &_DetectPointing_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t DetectPointing_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_DetectPointing_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &human_interfaces__srv__DetectPointing_Request__get_type_hash,
  &human_interfaces__srv__DetectPointing_Request__get_type_description,
  &human_interfaces__srv__DetectPointing_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace human_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, human_interfaces, srv, DetectPointing_Request)() {
  return &::human_interfaces::srv::rosidl_typesupport_c::DetectPointing_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "human_interfaces/srv/detail/detect_pointing__struct.h"
// already included above
// #include "human_interfaces/srv/detail/detect_pointing__type_support.h"
// already included above
// #include "human_interfaces/srv/detail/detect_pointing__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace human_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _DetectPointing_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _DetectPointing_Response_type_support_ids_t;

static const _DetectPointing_Response_type_support_ids_t _DetectPointing_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _DetectPointing_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _DetectPointing_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _DetectPointing_Response_type_support_symbol_names_t _DetectPointing_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, human_interfaces, srv, DetectPointing_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, human_interfaces, srv, DetectPointing_Response)),
  }
};

typedef struct _DetectPointing_Response_type_support_data_t
{
  void * data[2];
} _DetectPointing_Response_type_support_data_t;

static _DetectPointing_Response_type_support_data_t _DetectPointing_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _DetectPointing_Response_message_typesupport_map = {
  2,
  "human_interfaces",
  &_DetectPointing_Response_message_typesupport_ids.typesupport_identifier[0],
  &_DetectPointing_Response_message_typesupport_symbol_names.symbol_name[0],
  &_DetectPointing_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t DetectPointing_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_DetectPointing_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &human_interfaces__srv__DetectPointing_Response__get_type_hash,
  &human_interfaces__srv__DetectPointing_Response__get_type_description,
  &human_interfaces__srv__DetectPointing_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace human_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, human_interfaces, srv, DetectPointing_Response)() {
  return &::human_interfaces::srv::rosidl_typesupport_c::DetectPointing_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "human_interfaces/srv/detail/detect_pointing__struct.h"
// already included above
// #include "human_interfaces/srv/detail/detect_pointing__type_support.h"
// already included above
// #include "human_interfaces/srv/detail/detect_pointing__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace human_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _DetectPointing_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _DetectPointing_Event_type_support_ids_t;

static const _DetectPointing_Event_type_support_ids_t _DetectPointing_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _DetectPointing_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _DetectPointing_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _DetectPointing_Event_type_support_symbol_names_t _DetectPointing_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, human_interfaces, srv, DetectPointing_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, human_interfaces, srv, DetectPointing_Event)),
  }
};

typedef struct _DetectPointing_Event_type_support_data_t
{
  void * data[2];
} _DetectPointing_Event_type_support_data_t;

static _DetectPointing_Event_type_support_data_t _DetectPointing_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _DetectPointing_Event_message_typesupport_map = {
  2,
  "human_interfaces",
  &_DetectPointing_Event_message_typesupport_ids.typesupport_identifier[0],
  &_DetectPointing_Event_message_typesupport_symbol_names.symbol_name[0],
  &_DetectPointing_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t DetectPointing_Event_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_DetectPointing_Event_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &human_interfaces__srv__DetectPointing_Event__get_type_hash,
  &human_interfaces__srv__DetectPointing_Event__get_type_description,
  &human_interfaces__srv__DetectPointing_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace human_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, human_interfaces, srv, DetectPointing_Event)() {
  return &::human_interfaces::srv::rosidl_typesupport_c::DetectPointing_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "human_interfaces/srv/detail/detect_pointing__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
#include "service_msgs/msg/service_event_info.h"
#include "builtin_interfaces/msg/time.h"

namespace human_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{
typedef struct _DetectPointing_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _DetectPointing_type_support_ids_t;

static const _DetectPointing_type_support_ids_t _DetectPointing_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _DetectPointing_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _DetectPointing_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _DetectPointing_type_support_symbol_names_t _DetectPointing_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, human_interfaces, srv, DetectPointing)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, human_interfaces, srv, DetectPointing)),
  }
};

typedef struct _DetectPointing_type_support_data_t
{
  void * data[2];
} _DetectPointing_type_support_data_t;

static _DetectPointing_type_support_data_t _DetectPointing_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _DetectPointing_service_typesupport_map = {
  2,
  "human_interfaces",
  &_DetectPointing_service_typesupport_ids.typesupport_identifier[0],
  &_DetectPointing_service_typesupport_symbol_names.symbol_name[0],
  &_DetectPointing_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t DetectPointing_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_DetectPointing_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
  &DetectPointing_Request_message_type_support_handle,
  &DetectPointing_Response_message_type_support_handle,
  &DetectPointing_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    human_interfaces,
    srv,
    DetectPointing
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    human_interfaces,
    srv,
    DetectPointing
  ),
  &human_interfaces__srv__DetectPointing__get_type_hash,
  &human_interfaces__srv__DetectPointing__get_type_description,
  &human_interfaces__srv__DetectPointing__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace human_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, human_interfaces, srv, DetectPointing)() {
  return &::human_interfaces::srv::rosidl_typesupport_c::DetectPointing_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif
