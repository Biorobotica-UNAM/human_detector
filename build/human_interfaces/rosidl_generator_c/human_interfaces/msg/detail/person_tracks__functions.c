// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from human_interfaces:msg/PersonTracks.idl
// generated code does not contain a copyright notice
#include "human_interfaces/msg/detail/person_tracks__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `persons`
#include "human_interfaces/msg/detail/person_track__functions.h"

bool
human_interfaces__msg__PersonTracks__init(human_interfaces__msg__PersonTracks * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    human_interfaces__msg__PersonTracks__fini(msg);
    return false;
  }
  // persons
  if (!human_interfaces__msg__PersonTrack__Sequence__init(&msg->persons, 0)) {
    human_interfaces__msg__PersonTracks__fini(msg);
    return false;
  }
  return true;
}

void
human_interfaces__msg__PersonTracks__fini(human_interfaces__msg__PersonTracks * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // persons
  human_interfaces__msg__PersonTrack__Sequence__fini(&msg->persons);
}

bool
human_interfaces__msg__PersonTracks__are_equal(const human_interfaces__msg__PersonTracks * lhs, const human_interfaces__msg__PersonTracks * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // persons
  if (!human_interfaces__msg__PersonTrack__Sequence__are_equal(
      &(lhs->persons), &(rhs->persons)))
  {
    return false;
  }
  return true;
}

bool
human_interfaces__msg__PersonTracks__copy(
  const human_interfaces__msg__PersonTracks * input,
  human_interfaces__msg__PersonTracks * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // persons
  if (!human_interfaces__msg__PersonTrack__Sequence__copy(
      &(input->persons), &(output->persons)))
  {
    return false;
  }
  return true;
}

human_interfaces__msg__PersonTracks *
human_interfaces__msg__PersonTracks__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  human_interfaces__msg__PersonTracks * msg = (human_interfaces__msg__PersonTracks *)allocator.allocate(sizeof(human_interfaces__msg__PersonTracks), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(human_interfaces__msg__PersonTracks));
  bool success = human_interfaces__msg__PersonTracks__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
human_interfaces__msg__PersonTracks__destroy(human_interfaces__msg__PersonTracks * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    human_interfaces__msg__PersonTracks__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
human_interfaces__msg__PersonTracks__Sequence__init(human_interfaces__msg__PersonTracks__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  human_interfaces__msg__PersonTracks * data = NULL;

  if (size) {
    data = (human_interfaces__msg__PersonTracks *)allocator.zero_allocate(size, sizeof(human_interfaces__msg__PersonTracks), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = human_interfaces__msg__PersonTracks__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        human_interfaces__msg__PersonTracks__fini(&data[i - 1]);
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
human_interfaces__msg__PersonTracks__Sequence__fini(human_interfaces__msg__PersonTracks__Sequence * array)
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
      human_interfaces__msg__PersonTracks__fini(&array->data[i]);
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

human_interfaces__msg__PersonTracks__Sequence *
human_interfaces__msg__PersonTracks__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  human_interfaces__msg__PersonTracks__Sequence * array = (human_interfaces__msg__PersonTracks__Sequence *)allocator.allocate(sizeof(human_interfaces__msg__PersonTracks__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = human_interfaces__msg__PersonTracks__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
human_interfaces__msg__PersonTracks__Sequence__destroy(human_interfaces__msg__PersonTracks__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    human_interfaces__msg__PersonTracks__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
human_interfaces__msg__PersonTracks__Sequence__are_equal(const human_interfaces__msg__PersonTracks__Sequence * lhs, const human_interfaces__msg__PersonTracks__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!human_interfaces__msg__PersonTracks__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
human_interfaces__msg__PersonTracks__Sequence__copy(
  const human_interfaces__msg__PersonTracks__Sequence * input,
  human_interfaces__msg__PersonTracks__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(human_interfaces__msg__PersonTracks);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    human_interfaces__msg__PersonTracks * data =
      (human_interfaces__msg__PersonTracks *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!human_interfaces__msg__PersonTracks__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          human_interfaces__msg__PersonTracks__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!human_interfaces__msg__PersonTracks__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
