// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from human_interfaces:msg/PersonTrack.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "human_interfaces/msg/person_track.hpp"


#ifndef HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACK__STRUCT_HPP_
#define HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACK__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__human_interfaces__msg__PersonTrack __attribute__((deprecated))
#else
# define DEPRECATED__human_interfaces__msg__PersonTrack __declspec(deprecated)
#endif

namespace human_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PersonTrack_
{
  using Type = PersonTrack_<ContainerAllocator>;

  explicit PersonTrack_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0l;
      this->confidence = 0.0f;
    }
  }

  explicit PersonTrack_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0l;
      this->confidence = 0.0f;
    }
  }

  // field types and members
  using _id_type =
    int32_t;
  _id_type id;
  using _keypoints_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _keypoints_type keypoints;
  using _confidence_type =
    float;
  _confidence_type confidence;
  using _position_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _position_type position;

  // setters for named parameter idiom
  Type & set__id(
    const int32_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__keypoints(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->keypoints = _arg;
    return *this;
  }
  Type & set__confidence(
    const float & _arg)
  {
    this->confidence = _arg;
    return *this;
  }
  Type & set__position(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->position = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    human_interfaces::msg::PersonTrack_<ContainerAllocator> *;
  using ConstRawPtr =
    const human_interfaces::msg::PersonTrack_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<human_interfaces::msg::PersonTrack_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<human_interfaces::msg::PersonTrack_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      human_interfaces::msg::PersonTrack_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<human_interfaces::msg::PersonTrack_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      human_interfaces::msg::PersonTrack_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<human_interfaces::msg::PersonTrack_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<human_interfaces::msg::PersonTrack_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<human_interfaces::msg::PersonTrack_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__human_interfaces__msg__PersonTrack
    std::shared_ptr<human_interfaces::msg::PersonTrack_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__human_interfaces__msg__PersonTrack
    std::shared_ptr<human_interfaces::msg::PersonTrack_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PersonTrack_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->keypoints != other.keypoints) {
      return false;
    }
    if (this->confidence != other.confidence) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    return true;
  }
  bool operator!=(const PersonTrack_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PersonTrack_

// alias to use template instance with default allocator
using PersonTrack =
  human_interfaces::msg::PersonTrack_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace human_interfaces

#endif  // HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACK__STRUCT_HPP_
