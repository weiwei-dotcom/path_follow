// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from path_follow_interface:msg/Interface.idl
// generated code does not contain a copyright notice
#include "path_follow_interface/msg/detail/interface__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
path_follow_interface__msg__Interface__init(path_follow_interface__msg__Interface * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
path_follow_interface__msg__Interface__fini(path_follow_interface__msg__Interface * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
path_follow_interface__msg__Interface__are_equal(const path_follow_interface__msg__Interface * lhs, const path_follow_interface__msg__Interface * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
path_follow_interface__msg__Interface__copy(
  const path_follow_interface__msg__Interface * input,
  path_follow_interface__msg__Interface * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

path_follow_interface__msg__Interface *
path_follow_interface__msg__Interface__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  path_follow_interface__msg__Interface * msg = (path_follow_interface__msg__Interface *)allocator.allocate(sizeof(path_follow_interface__msg__Interface), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(path_follow_interface__msg__Interface));
  bool success = path_follow_interface__msg__Interface__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
path_follow_interface__msg__Interface__destroy(path_follow_interface__msg__Interface * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    path_follow_interface__msg__Interface__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
path_follow_interface__msg__Interface__Sequence__init(path_follow_interface__msg__Interface__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  path_follow_interface__msg__Interface * data = NULL;

  if (size) {
    data = (path_follow_interface__msg__Interface *)allocator.zero_allocate(size, sizeof(path_follow_interface__msg__Interface), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = path_follow_interface__msg__Interface__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        path_follow_interface__msg__Interface__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
path_follow_interface__msg__Interface__Sequence__fini(path_follow_interface__msg__Interface__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      path_follow_interface__msg__Interface__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

path_follow_interface__msg__Interface__Sequence *
path_follow_interface__msg__Interface__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  path_follow_interface__msg__Interface__Sequence * array = (path_follow_interface__msg__Interface__Sequence *)allocator.allocate(sizeof(path_follow_interface__msg__Interface__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = path_follow_interface__msg__Interface__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
path_follow_interface__msg__Interface__Sequence__destroy(path_follow_interface__msg__Interface__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    path_follow_interface__msg__Interface__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
path_follow_interface__msg__Interface__Sequence__are_equal(const path_follow_interface__msg__Interface__Sequence * lhs, const path_follow_interface__msg__Interface__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!path_follow_interface__msg__Interface__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
path_follow_interface__msg__Interface__Sequence__copy(
  const path_follow_interface__msg__Interface__Sequence * input,
  path_follow_interface__msg__Interface__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(path_follow_interface__msg__Interface);
    path_follow_interface__msg__Interface * data =
      (path_follow_interface__msg__Interface *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!path_follow_interface__msg__Interface__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          path_follow_interface__msg__Interface__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!path_follow_interface__msg__Interface__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
