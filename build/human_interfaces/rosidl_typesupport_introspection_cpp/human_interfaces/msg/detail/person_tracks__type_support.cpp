// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from human_interfaces:msg/PersonTracks.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "human_interfaces/msg/detail/person_tracks__functions.h"
#include "human_interfaces/msg/detail/person_tracks__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace human_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void PersonTracks_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) human_interfaces::msg::PersonTracks(_init);
}

void PersonTracks_fini_function(void * message_memory)
{
  auto typed_message = static_cast<human_interfaces::msg::PersonTracks *>(message_memory);
  typed_message->~PersonTracks();
}

size_t size_function__PersonTracks__persons(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<human_interfaces::msg::PersonTrack> *>(untyped_member);
  return member->size();
}

const void * get_const_function__PersonTracks__persons(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<human_interfaces::msg::PersonTrack> *>(untyped_member);
  return &member[index];
}

void * get_function__PersonTracks__persons(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<human_interfaces::msg::PersonTrack> *>(untyped_member);
  return &member[index];
}

void fetch_function__PersonTracks__persons(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const human_interfaces::msg::PersonTrack *>(
    get_const_function__PersonTracks__persons(untyped_member, index));
  auto & value = *reinterpret_cast<human_interfaces::msg::PersonTrack *>(untyped_value);
  value = item;
}

void assign_function__PersonTracks__persons(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<human_interfaces::msg::PersonTrack *>(
    get_function__PersonTracks__persons(untyped_member, index));
  const auto & value = *reinterpret_cast<const human_interfaces::msg::PersonTrack *>(untyped_value);
  item = value;
}

void resize_function__PersonTracks__persons(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<human_interfaces::msg::PersonTrack> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember PersonTracks_message_member_array[2] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(human_interfaces::msg::PersonTracks, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "persons",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<human_interfaces::msg::PersonTrack>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(human_interfaces::msg::PersonTracks, persons),  // bytes offset in struct
    nullptr,  // default value
    size_function__PersonTracks__persons,  // size() function pointer
    get_const_function__PersonTracks__persons,  // get_const(index) function pointer
    get_function__PersonTracks__persons,  // get(index) function pointer
    fetch_function__PersonTracks__persons,  // fetch(index, &value) function pointer
    assign_function__PersonTracks__persons,  // assign(index, value) function pointer
    resize_function__PersonTracks__persons  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers PersonTracks_message_members = {
  "human_interfaces::msg",  // message namespace
  "PersonTracks",  // message name
  2,  // number of fields
  sizeof(human_interfaces::msg::PersonTracks),
  false,  // has_any_key_member_
  PersonTracks_message_member_array,  // message members
  PersonTracks_init_function,  // function to initialize message memory (memory has to be allocated)
  PersonTracks_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t PersonTracks_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &PersonTracks_message_members,
  get_message_typesupport_handle_function,
  &human_interfaces__msg__PersonTracks__get_type_hash,
  &human_interfaces__msg__PersonTracks__get_type_description,
  &human_interfaces__msg__PersonTracks__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace human_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<human_interfaces::msg::PersonTracks>()
{
  return &::human_interfaces::msg::rosidl_typesupport_introspection_cpp::PersonTracks_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, human_interfaces, msg, PersonTracks)() {
  return &::human_interfaces::msg::rosidl_typesupport_introspection_cpp::PersonTracks_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
