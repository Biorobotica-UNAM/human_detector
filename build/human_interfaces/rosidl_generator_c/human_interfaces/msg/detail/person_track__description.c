// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from human_interfaces:msg/PersonTrack.idl
// generated code does not contain a copyright notice

#include "human_interfaces/msg/detail/person_track__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_human_interfaces
const rosidl_type_hash_t *
human_interfaces__msg__PersonTrack__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x03, 0x8a, 0xe2, 0xbd, 0xb3, 0x17, 0x67, 0xa4,
      0x52, 0x99, 0xa0, 0xc0, 0xf1, 0x73, 0x0f, 0x6f,
      0xf5, 0xc1, 0xca, 0x52, 0xed, 0x7c, 0x94, 0x83,
      0x19, 0x1b, 0x19, 0x99, 0x9c, 0x5a, 0x27, 0xa3,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char human_interfaces__msg__PersonTrack__TYPE_NAME[] = "human_interfaces/msg/PersonTrack";

// Define type names, field names, and default values
static char human_interfaces__msg__PersonTrack__FIELD_NAME__id[] = "id";
static char human_interfaces__msg__PersonTrack__FIELD_NAME__keypoints[] = "keypoints";
static char human_interfaces__msg__PersonTrack__FIELD_NAME__confidence[] = "confidence";
static char human_interfaces__msg__PersonTrack__FIELD_NAME__position[] = "position";

static rosidl_runtime_c__type_description__Field human_interfaces__msg__PersonTrack__FIELDS[] = {
  {
    {human_interfaces__msg__PersonTrack__FIELD_NAME__id, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {human_interfaces__msg__PersonTrack__FIELD_NAME__keypoints, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {human_interfaces__msg__PersonTrack__FIELD_NAME__confidence, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {human_interfaces__msg__PersonTrack__FIELD_NAME__position, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
human_interfaces__msg__PersonTrack__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {human_interfaces__msg__PersonTrack__TYPE_NAME, 32, 32},
      {human_interfaces__msg__PersonTrack__FIELDS, 4, 4},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "int32 id\n"
  "float32[] keypoints    # Arreglo plano de [x1, y1, c1, x2, y2, c2, ...]\n"
  "float32 confidence     # Confianza de la detecci\\xc3\\xb3n\n"
  "float32[] position     # Centroide [x, y] o [x, y, z]\n"
  "\n"
  "\n"
  "";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
human_interfaces__msg__PersonTrack__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {human_interfaces__msg__PersonTrack__TYPE_NAME, 32, 32},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 189, 189},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
human_interfaces__msg__PersonTrack__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *human_interfaces__msg__PersonTrack__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
