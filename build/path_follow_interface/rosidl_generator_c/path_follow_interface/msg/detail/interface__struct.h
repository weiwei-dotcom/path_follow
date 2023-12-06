// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from path_follow_interface:msg/Interface.idl
// generated code does not contain a copyright notice

#ifndef PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__STRUCT_H_
#define PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Interface in the package path_follow_interface.
typedef struct path_follow_interface__msg__Interface
{
  uint8_t structure_needs_at_least_one_member;
} path_follow_interface__msg__Interface;

// Struct for a sequence of path_follow_interface__msg__Interface.
typedef struct path_follow_interface__msg__Interface__Sequence
{
  path_follow_interface__msg__Interface * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} path_follow_interface__msg__Interface__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__STRUCT_H_
