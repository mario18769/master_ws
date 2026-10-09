// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from robot_interfaces:msg/ObjectPose.idl
// generated code does not contain a copyright notice

#include "robot_interfaces/msg/detail/object_pose__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_robot_interfaces
const rosidl_type_hash_t *
robot_interfaces__msg__ObjectPose__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x0c, 0x7d, 0x23, 0xff, 0xeb, 0x0c, 0x2f, 0x47,
      0xb2, 0x2b, 0x02, 0x18, 0xf6, 0x41, 0xbf, 0xdc,
      0x5f, 0xa9, 0x87, 0x24, 0xf1, 0x98, 0x74, 0x8a,
      0xa8, 0xfd, 0x37, 0xe3, 0x18, 0x74, 0x16, 0xb0,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char robot_interfaces__msg__ObjectPose__TYPE_NAME[] = "robot_interfaces/msg/ObjectPose";

// Define type names, field names, and default values
static char robot_interfaces__msg__ObjectPose__FIELD_NAME__object_type[] = "object_type";
static char robot_interfaces__msg__ObjectPose__FIELD_NAME__axis_x[] = "axis_x";
static char robot_interfaces__msg__ObjectPose__FIELD_NAME__axis_y[] = "axis_y";
static char robot_interfaces__msg__ObjectPose__FIELD_NAME__axis_z[] = "axis_z";
static char robot_interfaces__msg__ObjectPose__FIELD_NAME__axis_pt_x[] = "axis_pt_x";
static char robot_interfaces__msg__ObjectPose__FIELD_NAME__axis_pt_y[] = "axis_pt_y";
static char robot_interfaces__msg__ObjectPose__FIELD_NAME__axis_pt_z[] = "axis_pt_z";
static char robot_interfaces__msg__ObjectPose__FIELD_NAME__axis2_x[] = "axis2_x";
static char robot_interfaces__msg__ObjectPose__FIELD_NAME__axis2_y[] = "axis2_y";
static char robot_interfaces__msg__ObjectPose__FIELD_NAME__axis2_z[] = "axis2_z";
static char robot_interfaces__msg__ObjectPose__FIELD_NAME__radius[] = "radius";
static char robot_interfaces__msg__ObjectPose__FIELD_NAME__length[] = "length";
static char robot_interfaces__msg__ObjectPose__FIELD_NAME__mid_x[] = "mid_x";
static char robot_interfaces__msg__ObjectPose__FIELD_NAME__mid_y[] = "mid_y";
static char robot_interfaces__msg__ObjectPose__FIELD_NAME__mid_z[] = "mid_z";

static rosidl_runtime_c__type_description__Field robot_interfaces__msg__ObjectPose__FIELDS[] = {
  {
    {robot_interfaces__msg__ObjectPose__FIELD_NAME__object_type, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__ObjectPose__FIELD_NAME__axis_x, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__ObjectPose__FIELD_NAME__axis_y, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__ObjectPose__FIELD_NAME__axis_z, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__ObjectPose__FIELD_NAME__axis_pt_x, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__ObjectPose__FIELD_NAME__axis_pt_y, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__ObjectPose__FIELD_NAME__axis_pt_z, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__ObjectPose__FIELD_NAME__axis2_x, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__ObjectPose__FIELD_NAME__axis2_y, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__ObjectPose__FIELD_NAME__axis2_z, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__ObjectPose__FIELD_NAME__radius, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__ObjectPose__FIELD_NAME__length, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__ObjectPose__FIELD_NAME__mid_x, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__ObjectPose__FIELD_NAME__mid_y, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {robot_interfaces__msg__ObjectPose__FIELD_NAME__mid_z, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
robot_interfaces__msg__ObjectPose__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {robot_interfaces__msg__ObjectPose__TYPE_NAME, 31, 31},
      {robot_interfaces__msg__ObjectPose__FIELDS, 15, 15},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "string object_type\n"
  "\n"
  "float64 axis_x\n"
  "float64 axis_y\n"
  "float64 axis_z\n"
  "\n"
  "float64 axis_pt_x\n"
  "float64 axis_pt_y\n"
  "float64 axis_pt_z\n"
  "\n"
  "float64 axis2_x\n"
  "float64 axis2_y\n"
  "float64 axis2_z\n"
  "\n"
  "float64 radius\n"
  "float64 length\n"
  "\n"
  "float64 mid_x\n"
  "float64 mid_y\n"
  "float64 mid_z";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
robot_interfaces__msg__ObjectPose__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {robot_interfaces__msg__ObjectPose__TYPE_NAME, 31, 31},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 242, 242},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
robot_interfaces__msg__ObjectPose__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *robot_interfaces__msg__ObjectPose__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
