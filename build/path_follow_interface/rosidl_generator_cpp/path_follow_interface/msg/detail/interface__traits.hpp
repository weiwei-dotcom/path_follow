// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from path_follow_interface:msg/Interface.idl
// generated code does not contain a copyright notice

#ifndef PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__TRAITS_HPP_
#define PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__TRAITS_HPP_

#include "path_follow_interface/msg/detail/interface__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<path_follow_interface::msg::Interface>()
{
  return "path_follow_interface::msg::Interface";
}

template<>
inline const char * name<path_follow_interface::msg::Interface>()
{
  return "path_follow_interface/msg/Interface";
}

template<>
struct has_fixed_size<path_follow_interface::msg::Interface>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<path_follow_interface::msg::Interface>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<path_follow_interface::msg::Interface>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__TRAITS_HPP_
