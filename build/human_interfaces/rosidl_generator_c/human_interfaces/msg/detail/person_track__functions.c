// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from human_interfaces:msg/PersonTrack.idl
// generated code does not contain a copyright notice
#include "human_interfaces/msg/detail/person_track__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `keypoints`
// Member `position`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
human_interfaces__msg__PersonTrack__init(human_interfaces__msg__PersonTrack * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // keypoints
  if (!rosidl_runtime_c__float__Sequence__init(&msg->keypoints, 0)) {
    human_interfaces__msg__PersonTrack__fini(msg);
    return false;
  }
  // confidence
  // position
  if (!rosidl_runtime_c__float__Sequence__init(&msg->position, 0)) {
    human_interfaces__msg__PersonTrack__fini(msg);
    return false;
  }
  return true;
}

void
human_interfaces__msg__PersonTrack__fini(human_interfaces__msg__PersonTrack * msg)
{
  if (!msg) {
    return;
  }
  // id
  // keypoints
  rosidl_runtime_c__float__Sequence__fini(&msg->keypoints);
  // confidence
  // position
  rosidl_runtime_c__float__Sequence__fini(&msg->position);
}

bool
human_interfaces__msg__PersonTrack__are_equal(const human_interfaces__msg__PersonTrack * lhs, const human_interfaces__msg__PersonTrack * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // keypoints
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->keypoints), &(rhs->keypoints)))
  {
    return false;
  }
  // confidence
  if (lhs->confidence != rhs->confidence) {
    return false;
  }
  // position
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  return true;
}

bool
human_interfaces__msg__PersonTrack__copy(
  const human_interfaces__msg__PersonTrack * input,
  human_interfaces__msg__PersonTrack * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // keypoints
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->keypoints), &(output->keypoints)))
  {
    return false;
  }
  // confidence
  output->confidence = input->confidence;
  // position
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  return true;
}

human_interfaces__msg__PersonTrack *
human_interfaces__msg__PersonTrack__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  human_interfaces__msg__PersonTrack * msg = (human_interfaces__msg__PersonTrack *)allocator.allocate(sizeof(human_interfaces__msg__PersonTrack), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(human_interfaces__msg__PersonTrack));
  bool success = human_interfaces__msg__PersonTrack__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
human_interfaces__msg__PersonTrack__destroy(human_interfaces__msg__PersonTrack * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    human_interfaces__msg__PersonTrack__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
human_interfaces__msg__PersonTrack__Sequence__init(human_interfaces__msg__PersonTrack__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  human_interfaces__msg__PersonTrack * data = NULL;

  if (size) {
    data = (human_interfaces__msg__PersonTrack *)allocator.zero_allocate(size, sizeof(human_interfaces__msg__PersonTrack), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = human_interfaces__msg__PersonTrack__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        human_interfaces__msg__PersonTrack__fini(&data[i - 1]);
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
human_interfaces__msg__PersonTrack__Sequence__fini(human_interfaces__msg__PersonTrack__Sequence * array)
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
      human_interfaces__msg__PersonTrack__fini(&array->data[i]);
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

human_interfaces__msg__PersonTrack__Sequence *
human_interfaces__msg__PersonTrack__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  human_interfaces__msg__PersonTrack__Sequence * array = (human_interfaces__msg__PersonTrack__Sequence *)allocator.allocate(sizeof(human_interfaces__msg__PersonTrack__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = human_interfaces__msg__PersonTrack__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
human_interfaces__msg__PersonTrack__Sequence__destroy(human_interfaces__msg__PersonTrack__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    human_interfaces__msg__PersonTrack__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
human_interfaces__msg__PersonTrack__Sequence__are_equal(const human_interfaces__msg__PersonTrack__Sequence * lhs, const human_interfaces__msg__PersonTrack__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!human_interfaces__msg__PersonTrack__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
human_interfaces__msg__PersonTrack__Sequence__copy(
  const human_interfaces__msg__PersonTrack__Sequence * input,
  human_interfaces__msg__PersonTrack__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(human_interfaces__msg__PersonTrack);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    human_interfaces__msg__PersonTrack * data =
      (human_interfaces__msg__PersonTrack *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!human_interfaces__msg__PersonTrack__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          human_interfaces__msg__PersonTrack__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!human_interfaces__msg__PersonTrack__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
