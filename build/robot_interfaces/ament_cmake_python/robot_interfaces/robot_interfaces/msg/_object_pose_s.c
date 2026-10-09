// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from robot_interfaces:msg/ObjectPose.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "robot_interfaces/msg/detail/object_pose__struct.h"
#include "robot_interfaces/msg/detail/object_pose__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool robot_interfaces__msg__object_pose__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[45];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("robot_interfaces.msg._object_pose.ObjectPose", full_classname_dest, 44) == 0);
  }
  robot_interfaces__msg__ObjectPose * ros_message = _ros_message;
  {  // object_type
    PyObject * field = PyObject_GetAttrString(_pymsg, "object_type");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->object_type, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // axis_x
    PyObject * field = PyObject_GetAttrString(_pymsg, "axis_x");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->axis_x = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // axis_y
    PyObject * field = PyObject_GetAttrString(_pymsg, "axis_y");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->axis_y = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // axis_z
    PyObject * field = PyObject_GetAttrString(_pymsg, "axis_z");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->axis_z = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // axis_pt_x
    PyObject * field = PyObject_GetAttrString(_pymsg, "axis_pt_x");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->axis_pt_x = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // axis_pt_y
    PyObject * field = PyObject_GetAttrString(_pymsg, "axis_pt_y");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->axis_pt_y = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // axis_pt_z
    PyObject * field = PyObject_GetAttrString(_pymsg, "axis_pt_z");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->axis_pt_z = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // axis2_x
    PyObject * field = PyObject_GetAttrString(_pymsg, "axis2_x");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->axis2_x = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // axis2_y
    PyObject * field = PyObject_GetAttrString(_pymsg, "axis2_y");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->axis2_y = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // axis2_z
    PyObject * field = PyObject_GetAttrString(_pymsg, "axis2_z");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->axis2_z = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // radius
    PyObject * field = PyObject_GetAttrString(_pymsg, "radius");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->radius = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // length
    PyObject * field = PyObject_GetAttrString(_pymsg, "length");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->length = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // mid_x
    PyObject * field = PyObject_GetAttrString(_pymsg, "mid_x");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->mid_x = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // mid_y
    PyObject * field = PyObject_GetAttrString(_pymsg, "mid_y");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->mid_y = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // mid_z
    PyObject * field = PyObject_GetAttrString(_pymsg, "mid_z");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->mid_z = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * robot_interfaces__msg__object_pose__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of ObjectPose */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("robot_interfaces.msg._object_pose");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "ObjectPose");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  robot_interfaces__msg__ObjectPose * ros_message = (robot_interfaces__msg__ObjectPose *)raw_ros_message;
  {  // object_type
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->object_type.data,
      strlen(ros_message->object_type.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "object_type", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // axis_x
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->axis_x);
    {
      int rc = PyObject_SetAttrString(_pymessage, "axis_x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // axis_y
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->axis_y);
    {
      int rc = PyObject_SetAttrString(_pymessage, "axis_y", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // axis_z
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->axis_z);
    {
      int rc = PyObject_SetAttrString(_pymessage, "axis_z", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // axis_pt_x
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->axis_pt_x);
    {
      int rc = PyObject_SetAttrString(_pymessage, "axis_pt_x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // axis_pt_y
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->axis_pt_y);
    {
      int rc = PyObject_SetAttrString(_pymessage, "axis_pt_y", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // axis_pt_z
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->axis_pt_z);
    {
      int rc = PyObject_SetAttrString(_pymessage, "axis_pt_z", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // axis2_x
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->axis2_x);
    {
      int rc = PyObject_SetAttrString(_pymessage, "axis2_x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // axis2_y
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->axis2_y);
    {
      int rc = PyObject_SetAttrString(_pymessage, "axis2_y", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // axis2_z
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->axis2_z);
    {
      int rc = PyObject_SetAttrString(_pymessage, "axis2_z", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // radius
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->radius);
    {
      int rc = PyObject_SetAttrString(_pymessage, "radius", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // length
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->length);
    {
      int rc = PyObject_SetAttrString(_pymessage, "length", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mid_x
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->mid_x);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mid_x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mid_y
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->mid_y);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mid_y", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mid_z
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->mid_z);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mid_z", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
