// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from path_follow_interface:msg/Interface.idl
// generated code does not contain a copyright notice

#ifndef PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__STRUCT_HPP_
#define PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__path_follow_interface__msg__Interface __attribute__((deprecated))
#else
# define DEPRECATED__path_follow_interface__msg__Interface __declspec(deprecated)
#endif

namespace path_follow_interface
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Interface_
{
  using Type = Interface_<ContainerAllocator>;

  explicit Interface_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit Interface_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    path_follow_interface::msg::Interface_<ContainerAllocator> *;
  using ConstRawPtr =
    const path_follow_interface::msg::Interface_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<path_follow_interface::msg::Interface_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<path_follow_interface::msg::Interface_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      path_follow_interface::msg::Interface_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<path_follow_interface::msg::Interface_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      path_follow_interface::msg::Interface_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<path_follow_interface::msg::Interface_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<path_follow_interface::msg::Interface_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<path_follow_interface::msg::Interface_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__path_follow_interface__msg__Interface
    std::shared_ptr<path_follow_interface::msg::Interface_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__path_follow_interface__msg__Interface
    std::shared_ptr<path_follow_interface::msg::Interface_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Interface_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const Interface_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Interface_

// alias to use template instance with default allocator
using Interface =
  path_follow_interface::msg::Interface_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace path_follow_interface

#endif  // PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__STRUCT_HPP_
