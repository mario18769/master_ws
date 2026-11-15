// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from linkattacher_msgs:srv/DetachLink.idl
// generated code does not contain a copyright notice

#include "linkattacher_msgs/srv/detail/detach_link__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_linkattacher_msgs
const rosidl_type_hash_t *
linkattacher_msgs__srv__DetachLink__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x34, 0xc3, 0xf2, 0xc4, 0x3d, 0x88, 0xca, 0xc5,
      0x2a, 0x6f, 0x7b, 0xa6, 0x15, 0x6f, 0xfb, 0xe8,
      0x82, 0x0a, 0xb8, 0xee, 0x55, 0x90, 0x98, 0x55,
      0xcc, 0xe9, 0xa9, 0xe3, 0xfe, 0xa3, 0x32, 0x7f,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_linkattacher_msgs
const rosidl_type_hash_t *
linkattacher_msgs__srv__DetachLink_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x35, 0x5e, 0x7c, 0x05, 0x44, 0x2b, 0x30, 0xf8,
      0x9a, 0x3d, 0x3f, 0xea, 0xb3, 0x00, 0xc0, 0x8d,
      0x2f, 0x5c, 0xf6, 0x3d, 0x9e, 0xf6, 0x90, 0x82,
      0x97, 0x82, 0x4d, 0x5c, 0x21, 0x3e, 0x95, 0x9e,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_linkattacher_msgs
const rosidl_type_hash_t *
linkattacher_msgs__srv__DetachLink_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x48, 0x0b, 0xc4, 0x80, 0x82, 0xb8, 0xa0, 0xf3,
      0xca, 0xe5, 0x41, 0x12, 0x4b, 0xf9, 0xd9, 0xc7,
      0x6b, 0xf9, 0x75, 0xfe, 0x29, 0x47, 0x67, 0x72,
      0xa0, 0x31, 0xa9, 0x30, 0x81, 0x7e, 0xe5, 0x76,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_linkattacher_msgs
const rosidl_type_hash_t *
linkattacher_msgs__srv__DetachLink_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x01, 0x98, 0x53, 0xe4, 0x99, 0xba, 0xdf, 0x8a,
      0xcf, 0xd6, 0x68, 0x82, 0x8b, 0x06, 0x5b, 0x68,
      0xc9, 0x24, 0x57, 0x80, 0xc4, 0x8b, 0x66, 0xc7,
      0x40, 0xe6, 0xe4, 0xe8, 0xbe, 0x82, 0x6b, 0x9d,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "service_msgs/msg/detail/service_event_info__functions.h"
#include "builtin_interfaces/msg/detail/time__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t service_msgs__msg__ServiceEventInfo__EXPECTED_HASH = {1, {
    0x41, 0xbc, 0xbb, 0xe0, 0x7a, 0x75, 0xc9, 0xb5,
    0x2b, 0xc9, 0x6b, 0xfd, 0x5c, 0x24, 0xd7, 0xf0,
    0xfc, 0x0a, 0x08, 0xc0, 0xcb, 0x79, 0x21, 0xb3,
    0x37, 0x3c, 0x57, 0x32, 0x34, 0x5a, 0x6f, 0x45,
  }};
#endif

static char linkattacher_msgs__srv__DetachLink__TYPE_NAME[] = "linkattacher_msgs/srv/DetachLink";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char linkattacher_msgs__srv__DetachLink_Event__TYPE_NAME[] = "linkattacher_msgs/srv/DetachLink_Event";
static char linkattacher_msgs__srv__DetachLink_Request__TYPE_NAME[] = "linkattacher_msgs/srv/DetachLink_Request";
static char linkattacher_msgs__srv__DetachLink_Response__TYPE_NAME[] = "linkattacher_msgs/srv/DetachLink_Response";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";

// Define type names, field names, and default values
static char linkattacher_msgs__srv__DetachLink__FIELD_NAME__request_message[] = "request_message";
static char linkattacher_msgs__srv__DetachLink__FIELD_NAME__response_message[] = "response_message";
static char linkattacher_msgs__srv__DetachLink__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field linkattacher_msgs__srv__DetachLink__FIELDS[] = {
  {
    {linkattacher_msgs__srv__DetachLink__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {linkattacher_msgs__srv__DetachLink_Request__TYPE_NAME, 40, 40},
    },
    {NULL, 0, 0},
  },
  {
    {linkattacher_msgs__srv__DetachLink__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {linkattacher_msgs__srv__DetachLink_Response__TYPE_NAME, 41, 41},
    },
    {NULL, 0, 0},
  },
  {
    {linkattacher_msgs__srv__DetachLink__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {linkattacher_msgs__srv__DetachLink_Event__TYPE_NAME, 38, 38},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription linkattacher_msgs__srv__DetachLink__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {linkattacher_msgs__srv__DetachLink_Event__TYPE_NAME, 38, 38},
    {NULL, 0, 0},
  },
  {
    {linkattacher_msgs__srv__DetachLink_Request__TYPE_NAME, 40, 40},
    {NULL, 0, 0},
  },
  {
    {linkattacher_msgs__srv__DetachLink_Response__TYPE_NAME, 41, 41},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
linkattacher_msgs__srv__DetachLink__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {linkattacher_msgs__srv__DetachLink__TYPE_NAME, 32, 32},
      {linkattacher_msgs__srv__DetachLink__FIELDS, 3, 3},
    },
    {linkattacher_msgs__srv__DetachLink__REFERENCED_TYPE_DESCRIPTIONS, 5, 5},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[1].fields = linkattacher_msgs__srv__DetachLink_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = linkattacher_msgs__srv__DetachLink_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = linkattacher_msgs__srv__DetachLink_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char linkattacher_msgs__srv__DetachLink_Request__FIELD_NAME__model1_name[] = "model1_name";
static char linkattacher_msgs__srv__DetachLink_Request__FIELD_NAME__link1_name[] = "link1_name";
static char linkattacher_msgs__srv__DetachLink_Request__FIELD_NAME__model2_name[] = "model2_name";
static char linkattacher_msgs__srv__DetachLink_Request__FIELD_NAME__link2_name[] = "link2_name";

static rosidl_runtime_c__type_description__Field linkattacher_msgs__srv__DetachLink_Request__FIELDS[] = {
  {
    {linkattacher_msgs__srv__DetachLink_Request__FIELD_NAME__model1_name, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {linkattacher_msgs__srv__DetachLink_Request__FIELD_NAME__link1_name, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {linkattacher_msgs__srv__DetachLink_Request__FIELD_NAME__model2_name, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {linkattacher_msgs__srv__DetachLink_Request__FIELD_NAME__link2_name, 10, 10},
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
linkattacher_msgs__srv__DetachLink_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {linkattacher_msgs__srv__DetachLink_Request__TYPE_NAME, 40, 40},
      {linkattacher_msgs__srv__DetachLink_Request__FIELDS, 4, 4},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char linkattacher_msgs__srv__DetachLink_Response__FIELD_NAME__success[] = "success";
static char linkattacher_msgs__srv__DetachLink_Response__FIELD_NAME__message[] = "message";

static rosidl_runtime_c__type_description__Field linkattacher_msgs__srv__DetachLink_Response__FIELDS[] = {
  {
    {linkattacher_msgs__srv__DetachLink_Response__FIELD_NAME__success, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {linkattacher_msgs__srv__DetachLink_Response__FIELD_NAME__message, 7, 7},
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
linkattacher_msgs__srv__DetachLink_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {linkattacher_msgs__srv__DetachLink_Response__TYPE_NAME, 41, 41},
      {linkattacher_msgs__srv__DetachLink_Response__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char linkattacher_msgs__srv__DetachLink_Event__FIELD_NAME__info[] = "info";
static char linkattacher_msgs__srv__DetachLink_Event__FIELD_NAME__request[] = "request";
static char linkattacher_msgs__srv__DetachLink_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field linkattacher_msgs__srv__DetachLink_Event__FIELDS[] = {
  {
    {linkattacher_msgs__srv__DetachLink_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {linkattacher_msgs__srv__DetachLink_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {linkattacher_msgs__srv__DetachLink_Request__TYPE_NAME, 40, 40},
    },
    {NULL, 0, 0},
  },
  {
    {linkattacher_msgs__srv__DetachLink_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {linkattacher_msgs__srv__DetachLink_Response__TYPE_NAME, 41, 41},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription linkattacher_msgs__srv__DetachLink_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {linkattacher_msgs__srv__DetachLink_Request__TYPE_NAME, 40, 40},
    {NULL, 0, 0},
  },
  {
    {linkattacher_msgs__srv__DetachLink_Response__TYPE_NAME, 41, 41},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
linkattacher_msgs__srv__DetachLink_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {linkattacher_msgs__srv__DetachLink_Event__TYPE_NAME, 38, 38},
      {linkattacher_msgs__srv__DetachLink_Event__FIELDS, 3, 3},
    },
    {linkattacher_msgs__srv__DetachLink_Event__REFERENCED_TYPE_DESCRIPTIONS, 4, 4},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[1].fields = linkattacher_msgs__srv__DetachLink_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = linkattacher_msgs__srv__DetachLink_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "string model1_name    # Name of the first model.\n"
  "string link1_name     # Name of the link in the first model.\n"
  "string model2_name    # Name of the second model.\n"
  "string link2_name     # Name of the link in the second model.\n"
  "---\n"
  "bool success          # Whether the links were successfully attached or not.\n"
  "string message        # Feedback message.";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
linkattacher_msgs__srv__DetachLink__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {linkattacher_msgs__srv__DetachLink__TYPE_NAME, 32, 32},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 344, 344},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
linkattacher_msgs__srv__DetachLink_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {linkattacher_msgs__srv__DetachLink_Request__TYPE_NAME, 40, 40},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
linkattacher_msgs__srv__DetachLink_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {linkattacher_msgs__srv__DetachLink_Response__TYPE_NAME, 41, 41},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
linkattacher_msgs__srv__DetachLink_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {linkattacher_msgs__srv__DetachLink_Event__TYPE_NAME, 38, 38},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
linkattacher_msgs__srv__DetachLink__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[6];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 6, 6};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *linkattacher_msgs__srv__DetachLink__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *linkattacher_msgs__srv__DetachLink_Event__get_individual_type_description_source(NULL);
    sources[3] = *linkattacher_msgs__srv__DetachLink_Request__get_individual_type_description_source(NULL);
    sources[4] = *linkattacher_msgs__srv__DetachLink_Response__get_individual_type_description_source(NULL);
    sources[5] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
linkattacher_msgs__srv__DetachLink_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *linkattacher_msgs__srv__DetachLink_Request__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
linkattacher_msgs__srv__DetachLink_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *linkattacher_msgs__srv__DetachLink_Response__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
linkattacher_msgs__srv__DetachLink_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[5];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 5, 5};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *linkattacher_msgs__srv__DetachLink_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *linkattacher_msgs__srv__DetachLink_Request__get_individual_type_description_source(NULL);
    sources[3] = *linkattacher_msgs__srv__DetachLink_Response__get_individual_type_description_source(NULL);
    sources[4] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
