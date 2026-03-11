// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from human_interfaces:msg/PersonTrack.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "human_interfaces/msg/detail/person_track__rosidl_typesupport_introspection_c.h"
#include "human_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "human_interfaces/msg/detail/person_track__functions.h"
#include "human_interfaces/msg/detail/person_track__struct.h"


// Include directives for member types
// Member `keypoints`
// Member `position`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__PersonTrack_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  human_interfaces__msg__PersonTrack__init(message_memory);
}

void human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__PersonTrack_fini_function(void * message_memory)
{
  human_interfaces__msg__PersonTrack__fini(message_memory);
}

size_t human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__size_function__PersonTrack__keypoints(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__get_const_function__PersonTrack__keypoints(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__get_function__PersonTrack__keypoints(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__fetch_function__PersonTrack__keypoints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__get_const_function__PersonTrack__keypoints(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__assign_function__PersonTrack__keypoints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__get_function__PersonTrack__keypoints(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__resize_function__PersonTrack__keypoints(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__size_function__PersonTrack__position(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__get_const_function__PersonTrack__position(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__get_function__PersonTrack__position(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__fetch_function__PersonTrack__position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__get_const_function__PersonTrack__position(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__assign_function__PersonTrack__position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__get_function__PersonTrack__position(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__resize_function__PersonTrack__position(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__PersonTrack_message_member_array[4] = {
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(human_interfaces__msg__PersonTrack, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "keypoints",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(human_interfaces__msg__PersonTrack, keypoints),  // bytes offset in struct
    NULL,  // default value
    human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__size_function__PersonTrack__keypoints,  // size() function pointer
    human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__get_const_function__PersonTrack__keypoints,  // get_const(index) function pointer
    human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__get_function__PersonTrack__keypoints,  // get(index) function pointer
    human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__fetch_function__PersonTrack__keypoints,  // fetch(index, &value) function pointer
    human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__assign_function__PersonTrack__keypoints,  // assign(index, value) function pointer
    human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__resize_function__PersonTrack__keypoints  // resize(index) function pointer
  },
  {
    "confidence",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(human_interfaces__msg__PersonTrack, confidence),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(human_interfaces__msg__PersonTrack, position),  // bytes offset in struct
    NULL,  // default value
    human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__size_function__PersonTrack__position,  // size() function pointer
    human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__get_const_function__PersonTrack__position,  // get_const(index) function pointer
    human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__get_function__PersonTrack__position,  // get(index) function pointer
    human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__fetch_function__PersonTrack__position,  // fetch(index, &value) function pointer
    human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__assign_function__PersonTrack__position,  // assign(index, value) function pointer
    human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__resize_function__PersonTrack__position  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__PersonTrack_message_members = {
  "human_interfaces__msg",  // message namespace
  "PersonTrack",  // message name
  4,  // number of fields
  sizeof(human_interfaces__msg__PersonTrack),
  false,  // has_any_key_member_
  human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__PersonTrack_message_member_array,  // message members
  human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__PersonTrack_init_function,  // function to initialize message memory (memory has to be allocated)
  human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__PersonTrack_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__PersonTrack_message_type_support_handle = {
  0,
  &human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__PersonTrack_message_members,
  get_message_typesupport_handle_function,
  &human_interfaces__msg__PersonTrack__get_type_hash,
  &human_interfaces__msg__PersonTrack__get_type_description,
  &human_interfaces__msg__PersonTrack__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_human_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, human_interfaces, msg, PersonTrack)() {
  if (!human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__PersonTrack_message_type_support_handle.typesupport_identifier) {
    human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__PersonTrack_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &human_interfaces__msg__PersonTrack__rosidl_typesupport_introspection_c__PersonTrack_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
