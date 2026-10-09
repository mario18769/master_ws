// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_interfaces:msg/ObjectPose.idl
// generated code does not contain a copyright notice
#include "robot_interfaces/msg/detail/object_pose__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `object_type`
#include "rosidl_runtime_c/string_functions.h"

bool
robot_interfaces__msg__ObjectPose__init(robot_interfaces__msg__ObjectPose * msg)
{
  if (!msg) {
    return false;
  }
  // object_type
  if (!rosidl_runtime_c__String__init(&msg->object_type)) {
    robot_interfaces__msg__ObjectPose__fini(msg);
    return false;
  }
  // axis_x
  // axis_y
  // axis_z
  // axis_pt_x
  // axis_pt_y
  // axis_pt_z
  // axis2_x
  // axis2_y
  // axis2_z
  // radius
  // length
  // mid_x
  // mid_y
  // mid_z
  return true;
}

void
robot_interfaces__msg__ObjectPose__fini(robot_interfaces__msg__ObjectPose * msg)
{
  if (!msg) {
    return;
  }
  // object_type
  rosidl_runtime_c__String__fini(&msg->object_type);
  // axis_x
  // axis_y
  // axis_z
  // axis_pt_x
  // axis_pt_y
  // axis_pt_z
  // axis2_x
  // axis2_y
  // axis2_z
  // radius
  // length
  // mid_x
  // mid_y
  // mid_z
}

bool
robot_interfaces__msg__ObjectPose__are_equal(const robot_interfaces__msg__ObjectPose * lhs, const robot_interfaces__msg__ObjectPose * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // object_type
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->object_type), &(rhs->object_type)))
  {
    return false;
  }
  // axis_x
  if (lhs->axis_x != rhs->axis_x) {
    return false;
  }
  // axis_y
  if (lhs->axis_y != rhs->axis_y) {
    return false;
  }
  // axis_z
  if (lhs->axis_z != rhs->axis_z) {
    return false;
  }
  // axis_pt_x
  if (lhs->axis_pt_x != rhs->axis_pt_x) {
    return false;
  }
  // axis_pt_y
  if (lhs->axis_pt_y != rhs->axis_pt_y) {
    return false;
  }
  // axis_pt_z
  if (lhs->axis_pt_z != rhs->axis_pt_z) {
    return false;
  }
  // axis2_x
  if (lhs->axis2_x != rhs->axis2_x) {
    return false;
  }
  // axis2_y
  if (lhs->axis2_y != rhs->axis2_y) {
    return false;
  }
  // axis2_z
  if (lhs->axis2_z != rhs->axis2_z) {
    return false;
  }
  // radius
  if (lhs->radius != rhs->radius) {
    return false;
  }
  // length
  if (lhs->length != rhs->length) {
    return false;
  }
  // mid_x
  if (lhs->mid_x != rhs->mid_x) {
    return false;
  }
  // mid_y
  if (lhs->mid_y != rhs->mid_y) {
    return false;
  }
  // mid_z
  if (lhs->mid_z != rhs->mid_z) {
    return false;
  }
  return true;
}

bool
robot_interfaces__msg__ObjectPose__copy(
  const robot_interfaces__msg__ObjectPose * input,
  robot_interfaces__msg__ObjectPose * output)
{
  if (!input || !output) {
    return false;
  }
  // object_type
  if (!rosidl_runtime_c__String__copy(
      &(input->object_type), &(output->object_type)))
  {
    return false;
  }
  // axis_x
  output->axis_x = input->axis_x;
  // axis_y
  output->axis_y = input->axis_y;
  // axis_z
  output->axis_z = input->axis_z;
  // axis_pt_x
  output->axis_pt_x = input->axis_pt_x;
  // axis_pt_y
  output->axis_pt_y = input->axis_pt_y;
  // axis_pt_z
  output->axis_pt_z = input->axis_pt_z;
  // axis2_x
  output->axis2_x = input->axis2_x;
  // axis2_y
  output->axis2_y = input->axis2_y;
  // axis2_z
  output->axis2_z = input->axis2_z;
  // radius
  output->radius = input->radius;
  // length
  output->length = input->length;
  // mid_x
  output->mid_x = input->mid_x;
  // mid_y
  output->mid_y = input->mid_y;
  // mid_z
  output->mid_z = input->mid_z;
  return true;
}

robot_interfaces__msg__ObjectPose *
robot_interfaces__msg__ObjectPose__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_interfaces__msg__ObjectPose * msg = (robot_interfaces__msg__ObjectPose *)allocator.allocate(sizeof(robot_interfaces__msg__ObjectPose), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_interfaces__msg__ObjectPose));
  bool success = robot_interfaces__msg__ObjectPose__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_interfaces__msg__ObjectPose__destroy(robot_interfaces__msg__ObjectPose * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_interfaces__msg__ObjectPose__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_interfaces__msg__ObjectPose__Sequence__init(robot_interfaces__msg__ObjectPose__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_interfaces__msg__ObjectPose * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(robot_interfaces__msg__ObjectPose)) {
      return false;
    }
    data = (robot_interfaces__msg__ObjectPose *)allocator.zero_allocate(size, sizeof(robot_interfaces__msg__ObjectPose), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_interfaces__msg__ObjectPose__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_interfaces__msg__ObjectPose__fini(&data[i - 1]);
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
robot_interfaces__msg__ObjectPose__Sequence__fini(robot_interfaces__msg__ObjectPose__Sequence * array)
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
      robot_interfaces__msg__ObjectPose__fini(&array->data[i]);
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

robot_interfaces__msg__ObjectPose__Sequence *
robot_interfaces__msg__ObjectPose__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_interfaces__msg__ObjectPose__Sequence * array = (robot_interfaces__msg__ObjectPose__Sequence *)allocator.allocate(sizeof(robot_interfaces__msg__ObjectPose__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_interfaces__msg__ObjectPose__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_interfaces__msg__ObjectPose__Sequence__destroy(robot_interfaces__msg__ObjectPose__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_interfaces__msg__ObjectPose__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_interfaces__msg__ObjectPose__Sequence__are_equal(const robot_interfaces__msg__ObjectPose__Sequence * lhs, const robot_interfaces__msg__ObjectPose__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_interfaces__msg__ObjectPose__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_interfaces__msg__ObjectPose__Sequence__copy(
  const robot_interfaces__msg__ObjectPose__Sequence * input,
  robot_interfaces__msg__ObjectPose__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(robot_interfaces__msg__ObjectPose)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(robot_interfaces__msg__ObjectPose);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_interfaces__msg__ObjectPose * data =
      (robot_interfaces__msg__ObjectPose *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_interfaces__msg__ObjectPose__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_interfaces__msg__ObjectPose__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_interfaces__msg__ObjectPose__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
