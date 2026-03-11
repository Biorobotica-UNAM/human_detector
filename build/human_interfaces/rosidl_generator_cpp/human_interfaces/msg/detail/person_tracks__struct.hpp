// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from human_interfaces:msg/PersonTracks.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "human_interfaces/msg/person_tracks.hpp"


#ifndef HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACKS__STRUCT_HPP_
#define HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACKS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'persons'
#include "human_interfaces/msg/detail/person_track__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__human_interfaces__msg__PersonTracks __attribute__((deprecated))
#else
# define DEPRECATED__human_interfaces__msg__PersonTracks __declspec(deprecated)
#endif

namespace human_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PersonTracks_
{
  using Type = PersonTracks_<ContainerAllocator>;

  explicit PersonTracks_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit PersonTracks_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _persons_type =
    std::vector<human_interfaces::msg::PersonTrack_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<human_interfaces::msg::PersonTrack_<ContainerAllocator>>>;
  _persons_type persons;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__persons(
    const std::vector<human_interfaces::msg::PersonTrack_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<human_interfaces::msg::PersonTrack_<ContainerAllocator>>> & _arg)
  {
    this->persons = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    human_interfaces::msg::PersonTracks_<ContainerAllocator> *;
  using ConstRawPtr =
    const human_interfaces::msg::PersonTracks_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<human_interfaces::msg::PersonTracks_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<human_interfaces::msg::PersonTracks_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      human_interfaces::msg::PersonTracks_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<human_interfaces::msg::PersonTracks_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      human_interfaces::msg::PersonTracks_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<human_interfaces::msg::PersonTracks_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<human_interfaces::msg::PersonTracks_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<human_interfaces::msg::PersonTracks_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__human_interfaces__msg__PersonTracks
    std::shared_ptr<human_interfaces::msg::PersonTracks_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__human_interfaces__msg__PersonTracks
    std::shared_ptr<human_interfaces::msg::PersonTracks_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PersonTracks_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->persons != other.persons) {
      return false;
    }
    return true;
  }
  bool operator!=(const PersonTracks_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PersonTracks_

// alias to use template instance with default allocator
using PersonTracks =
  human_interfaces::msg::PersonTracks_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace human_interfaces

#endif  // HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACKS__STRUCT_HPP_
