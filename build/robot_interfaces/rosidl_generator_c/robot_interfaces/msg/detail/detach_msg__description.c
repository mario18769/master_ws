// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from robot_interfaces:msg/DetachMsg.idl
// generated code does not contain a copyright notice

#include "robot_interfaces/msg/detail/detach_msg__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_robot_interfaces
const rosidl_type_hash_t *
robot_interfaces__msg__DetachMsg__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x05, 0xcd, 0x9a, 0xa0, 0x67, 0xe6, 0x04, 0xd3,
      0x0f, 0x42, 0x92, 0xec, 0x15, 0x87, 0xa5, 0xf6,
      0x73, 0xca, 0x48, 0x98, 0x1e, 0x67, 0xb8, 0x78,
      0x30, 0x86, 0x14, 0x43, 0x11, 0xfc, 0x43, 0x62,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char robot_interfaces__msg__DetachMsg__TYPE_NAME[] = "robot_interfaces/msg/DetachMsg";

// Define type names, field names, and default values
static char robot_interfaces__msg__DetachMsg__FIELD_NAME__attach_msg[] = "attach_msg";
static char robot_interfaces__msg__DetachMsg__FIELD_NAME__detach_msg[] = "detach_msg";

static rosidl_runtime_c__type_description__Field robot_interfaces__msg__DetachMsg__FIELDS[] = {
  {
    {robot_interfaces__msg__DetachMsg__FIELD_NAME__attach_msg, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__DetachMsg__FIELD_NAME__detach_msg, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
robot_interfaces__msg__DetachMsg__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {robot_interfaces__msg__DetachMsg__TYPE_NAME, 30, 30},
      {robot_interfaces__msg__DetachMsg__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "\n"
  "string attach_msg\n"
  "string detach_msg";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
robot_interfaces__msg__DetachMsg__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {robot_interfaces__msg__DetachMsg__TYPE_NAME, 30, 30},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 36, 36},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
robot_interfaces__msg__DetachMsg__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *robot_interfaces__msg__DetachMsg__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
