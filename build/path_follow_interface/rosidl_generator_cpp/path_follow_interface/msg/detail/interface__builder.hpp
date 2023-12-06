// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from path_follow_interface:msg/Interface.idl
// generated code does not contain a copyright notice

#ifndef PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__BUILDER_HPP_
#define PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__BUILDER_HPP_

#include "path_follow_interface/msg/detail/interface__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace path_follow_interface
{

namespace msg
{


}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::path_follow_interface::msg::Interface>()
{
  return ::path_follow_interface::msg::Interface(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace path_follow_interface

#endif  // PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__BUILDER_HPP_
