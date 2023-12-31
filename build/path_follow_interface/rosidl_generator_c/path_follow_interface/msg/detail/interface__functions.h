// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from path_follow_interface:msg/Interface.idl
// generated code does not contain a copyright notice

#ifndef PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__FUNCTIONS_H_
#define PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "path_follow_interface/msg/rosidl_generator_c__visibility_control.h"

#include "path_follow_interface/msg/detail/interface__struct.h"

/// Initialize msg/Interface message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * path_follow_interface__msg__Interface
 * )) before or use
 * path_follow_interface__msg__Interface__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_path_follow_interface
bool
path_follow_interface__msg__Interface__init(path_follow_interface__msg__Interface * msg);

/// Finalize msg/Interface message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_path_follow_interface
void
path_follow_interface__msg__Interface__fini(path_follow_interface__msg__Interface * msg);

/// Create msg/Interface message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * path_follow_interface__msg__Interface__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_path_follow_interface
path_follow_interface__msg__Interface *
path_follow_interface__msg__Interface__create();

/// Destroy msg/Interface message.
/**
 * It calls
 * path_follow_interface__msg__Interface__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_path_follow_interface
void
path_follow_interface__msg__Interface__destroy(path_follow_interface__msg__Interface * msg);

/// Check for msg/Interface message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_path_follow_interface
bool
path_follow_interface__msg__Interface__are_equal(const path_follow_interface__msg__Interface * lhs, const path_follow_interface__msg__Interface * rhs);

/// Copy a msg/Interface message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_path_follow_interface
bool
path_follow_interface__msg__Interface__copy(
  const path_follow_interface__msg__Interface * input,
  path_follow_interface__msg__Interface * output);

/// Initialize array of msg/Interface messages.
/**
 * It allocates the memory for the number of elements and calls
 * path_follow_interface__msg__Interface__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_path_follow_interface
bool
path_follow_interface__msg__Interface__Sequence__init(path_follow_interface__msg__Interface__Sequence * array, size_t size);

/// Finalize array of msg/Interface messages.
/**
 * It calls
 * path_follow_interface__msg__Interface__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_path_follow_interface
void
path_follow_interface__msg__Interface__Sequence__fini(path_follow_interface__msg__Interface__Sequence * array);

/// Create array of msg/Interface messages.
/**
 * It allocates the memory for the array and calls
 * path_follow_interface__msg__Interface__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_path_follow_interface
path_follow_interface__msg__Interface__Sequence *
path_follow_interface__msg__Interface__Sequence__create(size_t size);

/// Destroy array of msg/Interface messages.
/**
 * It calls
 * path_follow_interface__msg__Interface__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_path_follow_interface
void
path_follow_interface__msg__Interface__Sequence__destroy(path_follow_interface__msg__Interface__Sequence * array);

/// Check for msg/Interface message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_path_follow_interface
bool
path_follow_interface__msg__Interface__Sequence__are_equal(const path_follow_interface__msg__Interface__Sequence * lhs, const path_follow_interface__msg__Interface__Sequence * rhs);

/// Copy an array of msg/Interface messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_path_follow_interface
bool
path_follow_interface__msg__Interface__Sequence__copy(
  const path_follow_interface__msg__Interface__Sequence * input,
  path_follow_interface__msg__Interface__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // PATH_FOLLOW_INTERFACE__MSG__DETAIL__INTERFACE__FUNCTIONS_H_
