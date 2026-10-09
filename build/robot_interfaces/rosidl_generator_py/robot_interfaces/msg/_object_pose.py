# generated from rosidl_generator_py/resource/_idl.py.em
# with input from robot_interfaces:msg/ObjectPose.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ObjectPose(type):
    """Metaclass of message 'ObjectPose'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('robot_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'robot_interfaces.msg.ObjectPose')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__object_pose
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__object_pose
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__object_pose
            cls._TYPE_SUPPORT = module.type_support_msg__msg__object_pose
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__object_pose

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ObjectPose(metaclass=Metaclass_ObjectPose):
    """Message class 'ObjectPose'."""

    __slots__ = [
        '_object_type',
        '_axis_x',
        '_axis_y',
        '_axis_z',
        '_axis_pt_x',
        '_axis_pt_y',
        '_axis_pt_z',
        '_axis2_x',
        '_axis2_y',
        '_axis2_z',
        '_radius',
        '_length',
        '_mid_x',
        '_mid_y',
        '_mid_z',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'object_type': 'string',
        'axis_x': 'double',
        'axis_y': 'double',
        'axis_z': 'double',
        'axis_pt_x': 'double',
        'axis_pt_y': 'double',
        'axis_pt_z': 'double',
        'axis2_x': 'double',
        'axis2_y': 'double',
        'axis2_z': 'double',
        'radius': 'double',
        'length': 'double',
        'mid_x': 'double',
        'mid_y': 'double',
        'mid_z': 'double',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.object_type = kwargs.get('object_type', str())
        self.axis_x = kwargs.get('axis_x', float())
        self.axis_y = kwargs.get('axis_y', float())
        self.axis_z = kwargs.get('axis_z', float())
        self.axis_pt_x = kwargs.get('axis_pt_x', float())
        self.axis_pt_y = kwargs.get('axis_pt_y', float())
        self.axis_pt_z = kwargs.get('axis_pt_z', float())
        self.axis2_x = kwargs.get('axis2_x', float())
        self.axis2_y = kwargs.get('axis2_y', float())
        self.axis2_z = kwargs.get('axis2_z', float())
        self.radius = kwargs.get('radius', float())
        self.length = kwargs.get('length', float())
        self.mid_x = kwargs.get('mid_x', float())
        self.mid_y = kwargs.get('mid_y', float())
        self.mid_z = kwargs.get('mid_z', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.object_type != other.object_type:
            return False
        if self.axis_x != other.axis_x:
            return False
        if self.axis_y != other.axis_y:
            return False
        if self.axis_z != other.axis_z:
            return False
        if self.axis_pt_x != other.axis_pt_x:
            return False
        if self.axis_pt_y != other.axis_pt_y:
            return False
        if self.axis_pt_z != other.axis_pt_z:
            return False
        if self.axis2_x != other.axis2_x:
            return False
        if self.axis2_y != other.axis2_y:
            return False
        if self.axis2_z != other.axis2_z:
            return False
        if self.radius != other.radius:
            return False
        if self.length != other.length:
            return False
        if self.mid_x != other.mid_x:
            return False
        if self.mid_y != other.mid_y:
            return False
        if self.mid_z != other.mid_z:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def object_type(self):
        """Message field 'object_type'."""
        return self._object_type

    @object_type.setter
    def object_type(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'object_type' field must be of type 'str'"
        self._object_type = value

    @builtins.property
    def axis_x(self):
        """Message field 'axis_x'."""
        return self._axis_x

    @axis_x.setter
    def axis_x(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'axis_x' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'axis_x' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._axis_x = value

    @builtins.property
    def axis_y(self):
        """Message field 'axis_y'."""
        return self._axis_y

    @axis_y.setter
    def axis_y(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'axis_y' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'axis_y' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._axis_y = value

    @builtins.property
    def axis_z(self):
        """Message field 'axis_z'."""
        return self._axis_z

    @axis_z.setter
    def axis_z(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'axis_z' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'axis_z' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._axis_z = value

    @builtins.property
    def axis_pt_x(self):
        """Message field 'axis_pt_x'."""
        return self._axis_pt_x

    @axis_pt_x.setter
    def axis_pt_x(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'axis_pt_x' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'axis_pt_x' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._axis_pt_x = value

    @builtins.property
    def axis_pt_y(self):
        """Message field 'axis_pt_y'."""
        return self._axis_pt_y

    @axis_pt_y.setter
    def axis_pt_y(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'axis_pt_y' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'axis_pt_y' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._axis_pt_y = value

    @builtins.property
    def axis_pt_z(self):
        """Message field 'axis_pt_z'."""
        return self._axis_pt_z

    @axis_pt_z.setter
    def axis_pt_z(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'axis_pt_z' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'axis_pt_z' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._axis_pt_z = value

    @builtins.property
    def axis2_x(self):
        """Message field 'axis2_x'."""
        return self._axis2_x

    @axis2_x.setter
    def axis2_x(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'axis2_x' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'axis2_x' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._axis2_x = value

    @builtins.property
    def axis2_y(self):
        """Message field 'axis2_y'."""
        return self._axis2_y

    @axis2_y.setter
    def axis2_y(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'axis2_y' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'axis2_y' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._axis2_y = value

    @builtins.property
    def axis2_z(self):
        """Message field 'axis2_z'."""
        return self._axis2_z

    @axis2_z.setter
    def axis2_z(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'axis2_z' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'axis2_z' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._axis2_z = value

    @builtins.property
    def radius(self):
        """Message field 'radius'."""
        return self._radius

    @radius.setter
    def radius(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'radius' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'radius' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._radius = value

    @builtins.property
    def length(self):
        """Message field 'length'."""
        return self._length

    @length.setter
    def length(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'length' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'length' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._length = value

    @builtins.property
    def mid_x(self):
        """Message field 'mid_x'."""
        return self._mid_x

    @mid_x.setter
    def mid_x(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'mid_x' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'mid_x' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._mid_x = value

    @builtins.property
    def mid_y(self):
        """Message field 'mid_y'."""
        return self._mid_y

    @mid_y.setter
    def mid_y(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'mid_y' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'mid_y' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._mid_y = value

    @builtins.property
    def mid_z(self):
        """Message field 'mid_z'."""
        return self._mid_z

    @mid_z.setter
    def mid_z(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'mid_z' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'mid_z' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._mid_z = value
