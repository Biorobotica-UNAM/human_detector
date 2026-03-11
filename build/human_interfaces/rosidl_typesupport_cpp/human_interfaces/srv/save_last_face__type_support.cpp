// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from human_interfaces:srv/SaveLastFace.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "human_interfaces/srv/detail/save_last_face__functions.h"
#include "human_interfaces/srv/detail/save_last_face__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace human_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _SaveLastFace_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SaveLastFace_Request_type_support_ids_t;

static const _SaveLastFace_Request_type_support_ids_t _SaveLastFace_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _SaveLastFace_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SaveLastFace_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SaveLastFace_Request_type_support_symbol_names_t _SaveLastFace_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, human_interfaces, srv, SaveLastFace_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, human_interfaces, srv, SaveLastFace_Request)),
  }
};

typedef struct _SaveLastFace_Request_type_support_data_t
{
  void * data[2];
} _SaveLastFace_Request_type_support_data_t;

static _SaveLastFace_Request_type_support_data_t _SaveLastFace_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SaveLastFace_Request_message_typesupport_map = {
  2,
  "human_interfaces",
  &_SaveLastFace_Request_message_typesupport_ids.typesupport_identifier[0],
  &_SaveLastFace_Request_message_typesupport_symbol_names.symbol_name[0],
  &_SaveLastFace_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SaveLastFace_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SaveLastFace_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &human_interfaces__srv__SaveLastFace_Request__get_type_hash,
  &human_interfaces__srv__SaveLastFace_Request__get_type_description,
  &human_interfaces__srv__SaveLastFace_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace human_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<human_interfaces::srv::SaveLastFace_Request>()
{
  return &::human_interfaces::srv::rosidl_typesupport_cpp::SaveLastFace_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, human_interfaces, srv, SaveLastFace_Request)() {
  return get_message_type_support_handle<human_interfaces::srv::SaveLastFace_Request>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "human_interfaces/srv/detail/save_last_face__functions.h"
// already included above
// #include "human_interfaces/srv/detail/save_last_face__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace human_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _SaveLastFace_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SaveLastFace_Response_type_support_ids_t;

static const _SaveLastFace_Response_type_support_ids_t _SaveLastFace_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _SaveLastFace_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SaveLastFace_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SaveLastFace_Response_type_support_symbol_names_t _SaveLastFace_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, human_interfaces, srv, SaveLastFace_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, human_interfaces, srv, SaveLastFace_Response)),
  }
};

typedef struct _SaveLastFace_Response_type_support_data_t
{
  void * data[2];
} _SaveLastFace_Response_type_support_data_t;

static _SaveLastFace_Response_type_support_data_t _SaveLastFace_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SaveLastFace_Response_message_typesupport_map = {
  2,
  "human_interfaces",
  &_SaveLastFace_Response_message_typesupport_ids.typesupport_identifier[0],
  &_SaveLastFace_Response_message_typesupport_symbol_names.symbol_name[0],
  &_SaveLastFace_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SaveLastFace_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SaveLastFace_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &human_interfaces__srv__SaveLastFace_Response__get_type_hash,
  &human_interfaces__srv__SaveLastFace_Response__get_type_description,
  &human_interfaces__srv__SaveLastFace_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace human_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<human_interfaces::srv::SaveLastFace_Response>()
{
  return &::human_interfaces::srv::rosidl_typesupport_cpp::SaveLastFace_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, human_interfaces, srv, SaveLastFace_Response)() {
  return get_message_type_support_handle<human_interfaces::srv::SaveLastFace_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "human_interfaces/srv/detail/save_last_face__functions.h"
// already included above
// #include "human_interfaces/srv/detail/save_last_face__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace human_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _SaveLastFace_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SaveLastFace_Event_type_support_ids_t;

static const _SaveLastFace_Event_type_support_ids_t _SaveLastFace_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _SaveLastFace_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SaveLastFace_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SaveLastFace_Event_type_support_symbol_names_t _SaveLastFace_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, human_interfaces, srv, SaveLastFace_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, human_interfaces, srv, SaveLastFace_Event)),
  }
};

typedef struct _SaveLastFace_Event_type_support_data_t
{
  void * data[2];
} _SaveLastFace_Event_type_support_data_t;

static _SaveLastFace_Event_type_support_data_t _SaveLastFace_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SaveLastFace_Event_message_typesupport_map = {
  2,
  "human_interfaces",
  &_SaveLastFace_Event_message_typesupport_ids.typesupport_identifier[0],
  &_SaveLastFace_Event_message_typesupport_symbol_names.symbol_name[0],
  &_SaveLastFace_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SaveLastFace_Event_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SaveLastFace_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &human_interfaces__srv__SaveLastFace_Event__get_type_hash,
  &human_interfaces__srv__SaveLastFace_Event__get_type_description,
  &human_interfaces__srv__SaveLastFace_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace human_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<human_interfaces::srv::SaveLastFace_Event>()
{
  return &::human_interfaces::srv::rosidl_typesupport_cpp::SaveLastFace_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, human_interfaces, srv, SaveLastFace_Event)() {
  return get_message_type_support_handle<human_interfaces::srv::SaveLastFace_Event>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "human_interfaces/srv/detail/save_last_face__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace human_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _SaveLastFace_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SaveLastFace_type_support_ids_t;

static const _SaveLastFace_type_support_ids_t _SaveLastFace_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _SaveLastFace_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SaveLastFace_type_support_symbol_names_t;
#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SaveLastFace_type_support_symbol_names_t _SaveLastFace_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, human_interfaces, srv, SaveLastFace)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, human_interfaces, srv, SaveLastFace)),
  }
};

typedef struct _SaveLastFace_type_support_data_t
{
  void * data[2];
} _SaveLastFace_type_support_data_t;

static _SaveLastFace_type_support_data_t _SaveLastFace_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SaveLastFace_service_typesupport_map = {
  2,
  "human_interfaces",
  &_SaveLastFace_service_typesupport_ids.typesupport_identifier[0],
  &_SaveLastFace_service_typesupport_symbol_names.symbol_name[0],
  &_SaveLastFace_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t SaveLastFace_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SaveLastFace_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<human_interfaces::srv::SaveLastFace_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<human_interfaces::srv::SaveLastFace_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<human_interfaces::srv::SaveLastFace_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<human_interfaces::srv::SaveLastFace>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<human_interfaces::srv::SaveLastFace>,
  &human_interfaces__srv__SaveLastFace__get_type_hash,
  &human_interfaces__srv__SaveLastFace__get_type_description,
  &human_interfaces__srv__SaveLastFace__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace human_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<human_interfaces::srv::SaveLastFace>()
{
  return &::human_interfaces::srv::rosidl_typesupport_cpp::SaveLastFace_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, human_interfaces, srv, SaveLastFace)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<human_interfaces::srv::SaveLastFace>();
}

#ifdef __cplusplus
}
#endif
