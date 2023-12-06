// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from path_follow_interface:msg/Interface.idl
// generated code does not contain a copyright notice

#ifndef PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "path_follow_interface/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "path_follow_interface/msg/detail/interface__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace path_follow_interface
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_path_follow_interface
cdr_serialize(
  const path_follow_interface::msg::Interface & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_path_follow_interface
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  path_follow_interface::msg::Interface & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_path_follow_interface
get_serialized_size(
  const path_follow_interface::msg::Interface & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_path_follow_interface
max_serialized_size_Interface(
  bool & full_bounded,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace path_follow_interface

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_path_follow_interface
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, path_follow_interface, msg, Interface)();

#ifdef __cplusplus
}
#endif

#endif  // PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
