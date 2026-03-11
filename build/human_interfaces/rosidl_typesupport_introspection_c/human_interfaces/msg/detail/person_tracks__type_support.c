// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from human_interfaces:msg/PersonTracks.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "human_interfaces/msg/detail/person_tracks__rosidl_typesupport_introspection_c.h"
#include "human_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "human_interfaces/msg/detail/person_tracks__functions.h"
#include "human_interfaces/msg/detail/person_tracks__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `persons`
#include "human_interfaces/msg/person_track.h"
// Member `persons`
#include "human_interfaces/msg/detail/person_track__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__PersonTracks_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  human_interfaces__msg__PersonTracks__init(message_memory);
}

void human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__PersonTracks_fini_function(void * message_memory)
{
  human_interfaces__msg__PersonTracks__fini(message_memory);
}

size_t human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__size_function__PersonTracks__persons(
  const void * untyped_member)
{
  const human_interfaces__msg__PersonTrack__Sequence * member =
    (const human_interfaces__msg__PersonTrack__Sequence *)(untyped_member);
  return member->size;
}

const void * human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__get_const_function__PersonTracks__persons(
  const void * untyped_member, size_t index)
{
  const human_interfaces__msg__PersonTrack__Sequence * member =
    (const human_interfaces__msg__PersonTrack__Sequence *)(untyped_member);
  return &member->data[index];
}

void * human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__get_function__PersonTracks__persons(
  void * untyped_member, size_t index)
{
  human_interfaces__msg__PersonTrack__Sequence * member =
    (human_interfaces__msg__PersonTrack__Sequence *)(untyped_member);
  return &member->data[index];
}

void human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__fetch_function__PersonTracks__persons(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const human_interfaces__msg__PersonTrack * item =
    ((const human_interfaces__msg__PersonTrack *)
    human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__get_const_function__PersonTracks__persons(untyped_member, index));
  human_interfaces__msg__PersonTrack * value =
    (human_interfaces__msg__PersonTrack *)(untyped_value);
  *value = *item;
}

void human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__assign_function__PersonTracks__persons(
  void * untyped_member, size_t index, const void * untyped_value)
{
  human_interfaces__msg__PersonTrack * item =
    ((human_interfaces__msg__PersonTrack *)
    human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__get_function__PersonTracks__persons(untyped_member, index));
  const human_interfaces__msg__PersonTrack * value =
    (const human_interfaces__msg__PersonTrack *)(untyped_value);
  *item = *value;
}

bool human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__resize_function__PersonTracks__persons(
  void * untyped_member, size_t size)
{
  human_interfaces__msg__PersonTrack__Sequence * member =
    (human_interfaces__msg__PersonTrack__Sequence *)(untyped_member);
  human_interfaces__msg__PersonTrack__Sequence__fini(member);
  return human_interfaces__msg__PersonTrack__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__PersonTracks_message_member_array[2] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(human_interfaces__msg__PersonTracks, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "persons",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(human_interfaces__msg__PersonTracks, persons),  // bytes offset in struct
    NULL,  // default value
    human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__size_function__PersonTracks__persons,  // size() function pointer
    human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__get_const_function__PersonTracks__persons,  // get_const(index) function pointer
    human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__get_function__PersonTracks__persons,  // get(index) function pointer
    human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__fetch_function__PersonTracks__persons,  // fetch(index, &value) function pointer
    human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__assign_function__PersonTracks__persons,  // assign(index, value) function pointer
    human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__resize_function__PersonTracks__persons  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__PersonTracks_message_members = {
  "human_interfaces__msg",  // message namespace
  "PersonTracks",  // message name
  2,  // number of fields
  sizeof(human_interfaces__msg__PersonTracks),
  false,  // has_any_key_member_
  human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__PersonTracks_message_member_array,  // message members
  human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__PersonTracks_init_function,  // function to initialize message memory (memory has to be allocated)
  human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__PersonTracks_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__PersonTracks_message_type_support_handle = {
  0,
  &human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__PersonTracks_message_members,
  get_message_typesupport_handle_function,
  &human_interfaces__msg__PersonTracks__get_type_hash,
  &human_interfaces__msg__PersonTracks__get_type_description,
  &human_interfaces__msg__PersonTracks__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_human_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, human_interfaces, msg, PersonTracks)() {
  human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__PersonTracks_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__PersonTracks_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, human_interfaces, msg, PersonTrack)();
  if (!human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__PersonTracks_message_type_support_handle.typesupport_identifier) {
    human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__PersonTracks_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &human_interfaces__msg__PersonTracks__rosidl_typesupport_introspection_c__PersonTracks_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
