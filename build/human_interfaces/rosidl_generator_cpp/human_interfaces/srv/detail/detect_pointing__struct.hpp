// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from human_interfaces:srv/DetectPointing.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "human_interfaces/srv/detect_pointing.hpp"


#ifndef HUMAN_INTERFACES__SRV__DETAIL__DETECT_POINTING__STRUCT_HPP_
#define HUMAN_INTERFACES__SRV__DETAIL__DETECT_POINTING__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__human_interfaces__srv__DetectPointing_Request __attribute__((deprecated))
#else
# define DEPRECATED__human_interfaces__srv__DetectPointing_Request __declspec(deprecated)
#endif

namespace human_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct DetectPointing_Request_
{
  using Type = DetectPointing_Request_<ContainerAllocator>;

  explicit DetectPointing_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit DetectPointing_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  // field types and members
  using _structure_needs_at_least_one_member_type =
    uint8_t;
  _structure_needs_at_least_one_member_type structure_needs_at_least_one_member;


  // constant declarations

  // pointer types
  using RawPtr =
    human_interfaces::srv::DetectPointing_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const human_interfaces::srv::DetectPointing_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<human_interfaces::srv::DetectPointing_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<human_interfaces::srv::DetectPointing_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      human_interfaces::srv::DetectPointing_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<human_interfaces::srv::DetectPointing_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      human_interfaces::srv::DetectPointing_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<human_interfaces::srv::DetectPointing_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<human_interfaces::srv::DetectPointing_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<human_interfaces::srv::DetectPointing_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__human_interfaces__srv__DetectPointing_Request
    std::shared_ptr<human_interfaces::srv::DetectPointing_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__human_interfaces__srv__DetectPointing_Request
    std::shared_ptr<human_interfaces::srv::DetectPointing_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DetectPointing_Request_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const DetectPointing_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DetectPointing_Request_

// alias to use template instance with default allocator
using DetectPointing_Request =
  human_interfaces::srv::DetectPointing_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace human_interfaces


// Include directives for member types
// Member 'pose_image'
#include "sensor_msgs/msg/detail/image__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__human_interfaces__srv__DetectPointing_Response __attribute__((deprecated))
#else
# define DEPRECATED__human_interfaces__srv__DetectPointing_Response __declspec(deprecated)
#endif

namespace human_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct DetectPointing_Response_
{
  using Type = DetectPointing_Response_<ContainerAllocator>;

  explicit DetectPointing_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose_image(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->human_detected = false;
      this->target_x = 0l;
      this->target_y = 0l;
      this->target_z = 0.0f;
      this->direction = "";
    }
  }

  explicit DetectPointing_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : direction(_alloc),
    pose_image(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->human_detected = false;
      this->target_x = 0l;
      this->target_y = 0l;
      this->target_z = 0.0f;
      this->direction = "";
    }
  }

  // field types and members
  using _human_detected_type =
    bool;
  _human_detected_type human_detected;
  using _target_x_type =
    int32_t;
  _target_x_type target_x;
  using _target_y_type =
    int32_t;
  _target_y_type target_y;
  using _target_z_type =
    float;
  _target_z_type target_z;
  using _direction_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _direction_type direction;
  using _pose_image_type =
    sensor_msgs::msg::Image_<ContainerAllocator>;
  _pose_image_type pose_image;

  // setters for named parameter idiom
  Type & set__human_detected(
    const bool & _arg)
  {
    this->human_detected = _arg;
    return *this;
  }
  Type & set__target_x(
    const int32_t & _arg)
  {
    this->target_x = _arg;
    return *this;
  }
  Type & set__target_y(
    const int32_t & _arg)
  {
    this->target_y = _arg;
    return *this;
  }
  Type & set__target_z(
    const float & _arg)
  {
    this->target_z = _arg;
    return *this;
  }
  Type & set__direction(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->direction = _arg;
    return *this;
  }
  Type & set__pose_image(
    const sensor_msgs::msg::Image_<ContainerAllocator> & _arg)
  {
    this->pose_image = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    human_interfaces::srv::DetectPointing_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const human_interfaces::srv::DetectPointing_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<human_interfaces::srv::DetectPointing_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<human_interfaces::srv::DetectPointing_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      human_interfaces::srv::DetectPointing_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<human_interfaces::srv::DetectPointing_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      human_interfaces::srv::DetectPointing_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<human_interfaces::srv::DetectPointing_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<human_interfaces::srv::DetectPointing_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<human_interfaces::srv::DetectPointing_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__human_interfaces__srv__DetectPointing_Response
    std::shared_ptr<human_interfaces::srv::DetectPointing_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__human_interfaces__srv__DetectPointing_Response
    std::shared_ptr<human_interfaces::srv::DetectPointing_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DetectPointing_Response_ & other) const
  {
    if (this->human_detected != other.human_detected) {
      return false;
    }
    if (this->target_x != other.target_x) {
      return false;
    }
    if (this->target_y != other.target_y) {
      return false;
    }
    if (this->target_z != other.target_z) {
      return false;
    }
    if (this->direction != other.direction) {
      return false;
    }
    if (this->pose_image != other.pose_image) {
      return false;
    }
    return true;
  }
  bool operator!=(const DetectPointing_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DetectPointing_Response_

// alias to use template instance with default allocator
using DetectPointing_Response =
  human_interfaces::srv::DetectPointing_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace human_interfaces


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__human_interfaces__srv__DetectPointing_Event __attribute__((deprecated))
#else
# define DEPRECATED__human_interfaces__srv__DetectPointing_Event __declspec(deprecated)
#endif

namespace human_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct DetectPointing_Event_
{
  using Type = DetectPointing_Event_<ContainerAllocator>;

  explicit DetectPointing_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit DetectPointing_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<human_interfaces::srv::DetectPointing_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<human_interfaces::srv::DetectPointing_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<human_interfaces::srv::DetectPointing_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<human_interfaces::srv::DetectPointing_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<human_interfaces::srv::DetectPointing_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<human_interfaces::srv::DetectPointing_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<human_interfaces::srv::DetectPointing_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<human_interfaces::srv::DetectPointing_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    human_interfaces::srv::DetectPointing_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const human_interfaces::srv::DetectPointing_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<human_interfaces::srv::DetectPointing_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<human_interfaces::srv::DetectPointing_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      human_interfaces::srv::DetectPointing_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<human_interfaces::srv::DetectPointing_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      human_interfaces::srv::DetectPointing_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<human_interfaces::srv::DetectPointing_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<human_interfaces::srv::DetectPointing_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<human_interfaces::srv::DetectPointing_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__human_interfaces__srv__DetectPointing_Event
    std::shared_ptr<human_interfaces::srv::DetectPointing_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__human_interfaces__srv__DetectPointing_Event
    std::shared_ptr<human_interfaces::srv::DetectPointing_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DetectPointing_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const DetectPointing_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DetectPointing_Event_

// alias to use template instance with default allocator
using DetectPointing_Event =
  human_interfaces::srv::DetectPointing_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace human_interfaces

namespace human_interfaces
{

namespace srv
{

struct DetectPointing
{
  using Request = human_interfaces::srv::DetectPointing_Request;
  using Response = human_interfaces::srv::DetectPointing_Response;
  using Event = human_interfaces::srv::DetectPointing_Event;
};

}  // namespace srv

}  // namespace human_interfaces

#endif  // HUMAN_INTERFACES__SRV__DETAIL__DETECT_POINTING__STRUCT_HPP_
