// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from human_interfaces:msg/PersonTracks.idl
// generated code does not contain a copyright notice

#include "human_interfaces/msg/detail/person_tracks__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_human_interfaces
const rosidl_type_hash_t *
human_interfaces__msg__PersonTracks__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x97, 0x71, 0xaf, 0x48, 0x3d, 0x02, 0xa0, 0xf2,
      0xb2, 0xcb, 0x6f, 0x70, 0x65, 0x8a, 0x97, 0x46,
      0x4b, 0x43, 0x2d, 0x36, 0xe4, 0x48, 0x07, 0xd2,
      0xe2, 0x38, 0x4f, 0xae, 0x38, 0xb5, 0x05, 0xb6,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "std_msgs/msg/detail/header__functions.h"
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "human_interfaces/msg/detail/person_track__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t human_interfaces__msg__PersonTrack__EXPECTED_HASH = {1, {
    0x03, 0x8a, 0xe2, 0xbd, 0xb3, 0x17, 0x67, 0xa4,
    0x52, 0x99, 0xa0, 0xc0, 0xf1, 0x73, 0x0f, 0x6f,
    0xf5, 0xc1, 0xca, 0x52, 0xed, 0x7c, 0x94, 0x83,
    0x19, 0x1b, 0x19, 0x99, 0x9c, 0x5a, 0x27, 0xa3,
  }};
static const rosidl_type_hash_t std_msgs__msg__Header__EXPECTED_HASH = {1, {
    0xf4, 0x9f, 0xb3, 0xae, 0x2c, 0xf0, 0x70, 0xf7,
    0x93, 0x64, 0x5f, 0xf7, 0x49, 0x68, 0x3a, 0xc6,
    0xb0, 0x62, 0x03, 0xe4, 0x1c, 0x89, 0x1e, 0x17,
    0x70, 0x1b, 0x1c, 0xb5, 0x97, 0xce, 0x6a, 0x01,
  }};
#endif

static char human_interfaces__msg__PersonTracks__TYPE_NAME[] = "human_interfaces/msg/PersonTracks";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char human_interfaces__msg__PersonTrack__TYPE_NAME[] = "human_interfaces/msg/PersonTrack";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";

// Define type names, field names, and default values
static char human_interfaces__msg__PersonTracks__FIELD_NAME__header[] = "header";
static char human_interfaces__msg__PersonTracks__FIELD_NAME__persons[] = "persons";

static rosidl_runtime_c__type_description__Field human_interfaces__msg__PersonTracks__FIELDS[] = {
  {
    {human_interfaces__msg__PersonTracks__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {human_interfaces__msg__PersonTracks__FIELD_NAME__persons, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {human_interfaces__msg__PersonTrack__TYPE_NAME, 32, 32},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription human_interfaces__msg__PersonTracks__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {human_interfaces__msg__PersonTrack__TYPE_NAME, 32, 32},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
human_interfaces__msg__PersonTracks__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {human_interfaces__msg__PersonTracks__TYPE_NAME, 33, 33},
      {human_interfaces__msg__PersonTracks__FIELDS, 2, 2},
    },
    {human_interfaces__msg__PersonTracks__REFERENCED_TYPE_DESCRIPTIONS, 3, 3},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&human_interfaces__msg__PersonTrack__EXPECTED_HASH, human_interfaces__msg__PersonTrack__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = human_interfaces__msg__PersonTrack__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "std_msgs/Header header\n"
  "PersonTrack[] persons\n"
  "\n"
  "\n"
  "";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
human_interfaces__msg__PersonTracks__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {human_interfaces__msg__PersonTracks__TYPE_NAME, 33, 33},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 48, 48},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
human_interfaces__msg__PersonTracks__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[4];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 4, 4};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *human_interfaces__msg__PersonTracks__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *human_interfaces__msg__PersonTrack__get_individual_type_description_source(NULL);
    sources[3] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
