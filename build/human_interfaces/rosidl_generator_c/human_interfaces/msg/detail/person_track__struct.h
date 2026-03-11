// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from human_interfaces:msg/PersonTrack.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "human_interfaces/msg/person_track.h"


#ifndef HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACK__STRUCT_H_
#define HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'keypoints'
// Member 'position'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/PersonTrack in the package human_interfaces.
typedef struct human_interfaces__msg__PersonTrack
{
  int32_t id;
  /// Arreglo plano de [x1, y1, c1, x2, y2, c2, ...]
  rosidl_runtime_c__float__Sequence keypoints;
  /// Confianza de la detección
  float confidence;
  /// Centroide [x, y] o [x, y, z]
  rosidl_runtime_c__float__Sequence position;
} human_interfaces__msg__PersonTrack;

// Struct for a sequence of human_interfaces__msg__PersonTrack.
typedef struct human_interfaces__msg__PersonTrack__Sequence
{
  human_interfaces__msg__PersonTrack * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} human_interfaces__msg__PersonTrack__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HUMAN_INTERFACES__MSG__DETAIL__PERSON_TRACK__STRUCT_H_
