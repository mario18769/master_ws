// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_interfaces:msg/DetachMsg.idl
// generated code does not contain a copyright notice
#include "robot_interfaces/msg/detail/detach_msg__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `attach_msg`
// Member `detach_msg`
#include "rosidl_runtime_c/string_functions.h"

bool
robot_interfaces__msg__DetachMsg__init(robot_interfaces__msg__DetachMsg * msg)
{
  if (!msg) {
    return false;
  }
  // attach_msg
  if (!rosidl_runtime_c__String__init(&msg->attach_msg)) {
    robot_interfaces__msg__DetachMsg__fini(msg);
    return false;
  }
  // detach_msg
  if (!rosidl_runtime_c__String__init(&msg->detach_msg)) {
    robot_interfaces__msg__DetachMsg__fini(msg);
    return false;
  }
  return true;
}

void
robot_interfaces__msg__DetachMsg__fini(robot_interfaces__msg__DetachMsg * msg)
{
  if (!msg) {
    return;
  }
  // attach_msg
  rosidl_runtime_c__String__fini(&msg->attach_msg);
  // detach_msg
  rosidl_runtime_c__String__fini(&msg->detach_msg);
}

bool
robot_interfaces__msg__DetachMsg__are_equal(const robot_interfaces__msg__DetachMsg * lhs, const robot_interfaces__msg__DetachMsg * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // attach_msg
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->attach_msg), &(rhs->attach_msg)))
  {
    return false;
  }
  // detach_msg
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->detach_msg), &(rhs->detach_msg)))
  {
    return false;
  }
  return true;
}

bool
robot_interfaces__msg__DetachMsg__copy(
  const robot_interfaces__msg__DetachMsg * input,
  robot_interfaces__msg__DetachMsg * output)
{
  if (!input || !output) {
    return false;
  }
  // attach_msg
  if (!rosidl_runtime_c__String__copy(
      &(input->attach_msg), &(output->attach_msg)))
  {
    return false;
  }
  // detach_msg
  if (!rosidl_runtime_c__String__copy(
      &(input->detach_msg), &(output->detach_msg)))
  {
    return false;
  }
  return true;
}

robot_interfaces__msg__DetachMsg *
robot_interfaces__msg__DetachMsg__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_interfaces__msg__DetachMsg * msg = (robot_interfaces__msg__DetachMsg *)allocator.allocate(sizeof(robot_interfaces__msg__DetachMsg), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_interfaces__msg__DetachMsg));
  bool success = robot_interfaces__msg__DetachMsg__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_interfaces__msg__DetachMsg__destroy(robot_interfaces__msg__DetachMsg * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_interfaces__msg__DetachMsg__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_interfaces__msg__DetachMsg__Sequence__init(robot_interfaces__msg__DetachMsg__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_interfaces__msg__DetachMsg * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(robot_interfaces__msg__DetachMsg)) {
      return false;
    }
    data = (robot_interfaces__msg__DetachMsg *)allocator.zero_allocate(size, sizeof(robot_interfaces__msg__DetachMsg), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_interfaces__msg__DetachMsg__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_interfaces__msg__DetachMsg__fini(&data[i - 1]);
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
robot_interfaces__msg__DetachMsg__Sequence__fini(robot_interfaces__msg__DetachMsg__Sequence * array)
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
      robot_interfaces__msg__DetachMsg__fini(&array->data[i]);
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

robot_interfaces__msg__DetachMsg__Sequence *
robot_interfaces__msg__DetachMsg__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_interfaces__msg__DetachMsg__Sequence * array = (robot_interfaces__msg__DetachMsg__Sequence *)allocator.allocate(sizeof(robot_interfaces__msg__DetachMsg__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_interfaces__msg__DetachMsg__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_interfaces__msg__DetachMsg__Sequence__destroy(robot_interfaces__msg__DetachMsg__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_interfaces__msg__DetachMsg__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_interfaces__msg__DetachMsg__Sequence__are_equal(const robot_interfaces__msg__DetachMsg__Sequence * lhs, const robot_interfaces__msg__DetachMsg__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_interfaces__msg__DetachMsg__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_interfaces__msg__DetachMsg__Sequence__copy(
  const robot_interfaces__msg__DetachMsg__Sequence * input,
  robot_interfaces__msg__DetachMsg__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(robot_interfaces__msg__DetachMsg)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(robot_interfaces__msg__DetachMsg);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_interfaces__msg__DetachMsg * data =
      (robot_interfaces__msg__DetachMsg *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_interfaces__msg__DetachMsg__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_interfaces__msg__DetachMsg__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_interfaces__msg__DetachMsg__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
