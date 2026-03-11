# generated from rosidl_generator_py/resource/_idl.py.em
# with input from human_interfaces:srv/DetectPointing.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_DetectPointing_Request(type):
    """Metaclass of message 'DetectPointing_Request'."""

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
            module = import_type_support('human_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'human_interfaces.srv.DetectPointing_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__detect_pointing__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__detect_pointing__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__detect_pointing__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__detect_pointing__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__detect_pointing__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class DetectPointing_Request(metaclass=Metaclass_DetectPointing_Request):
    """Message class 'DetectPointing_Request'."""

    __slots__ = [
        '_check_fields',
    ]

    _fields_and_field_types = {
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
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
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

# already imported above
# import rosidl_parser.definition


class Metaclass_DetectPointing_Response(type):
    """Metaclass of message 'DetectPointing_Response'."""

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
            module = import_type_support('human_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'human_interfaces.srv.DetectPointing_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__detect_pointing__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__detect_pointing__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__detect_pointing__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__detect_pointing__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__detect_pointing__response

            from sensor_msgs.msg import Image
            if Image.__class__._TYPE_SUPPORT is None:
                Image.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class DetectPointing_Response(metaclass=Metaclass_DetectPointing_Response):
    """Message class 'DetectPointing_Response'."""

    __slots__ = [
        '_human_detected',
        '_target_x',
        '_target_y',
        '_target_z',
        '_direction',
        '_pose_image',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'human_detected': 'boolean',
        'target_x': 'int32',
        'target_y': 'int32',
        'target_z': 'float',
        'direction': 'string',
        'pose_image': 'sensor_msgs/Image',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['sensor_msgs', 'msg'], 'Image'),  # noqa: E501
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
        self.human_detected = kwargs.get('human_detected', bool())
        self.target_x = kwargs.get('target_x', int())
        self.target_y = kwargs.get('target_y', int())
        self.target_z = kwargs.get('target_z', float())
        self.direction = kwargs.get('direction', str())
        from sensor_msgs.msg import Image
        self.pose_image = kwargs.get('pose_image', Image())

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
        if self.human_detected != other.human_detected:
            return False
        if self.target_x != other.target_x:
            return False
        if self.target_y != other.target_y:
            return False
        if self.target_z != other.target_z:
            return False
        if self.direction != other.direction:
            return False
        if self.pose_image != other.pose_image:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def human_detected(self):
        """Message field 'human_detected'."""
        return self._human_detected

    @human_detected.setter
    def human_detected(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'human_detected' field must be of type 'bool'"
        self._human_detected = value

    @builtins.property
    def target_x(self):
        """Message field 'target_x'."""
        return self._target_x

    @target_x.setter
    def target_x(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'target_x' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'target_x' field must be an integer in [-2147483648, 2147483647]"
        self._target_x = value

    @builtins.property
    def target_y(self):
        """Message field 'target_y'."""
        return self._target_y

    @target_y.setter
    def target_y(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'target_y' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'target_y' field must be an integer in [-2147483648, 2147483647]"
        self._target_y = value

    @builtins.property
    def target_z(self):
        """Message field 'target_z'."""
        return self._target_z

    @target_z.setter
    def target_z(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'target_z' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'target_z' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._target_z = value

    @builtins.property
    def direction(self):
        """Message field 'direction'."""
        return self._direction

    @direction.setter
    def direction(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'direction' field must be of type 'str'"
        self._direction = value

    @builtins.property
    def pose_image(self):
        """Message field 'pose_image'."""
        return self._pose_image

    @pose_image.setter
    def pose_image(self, value):
        if self._check_fields:
            from sensor_msgs.msg import Image
            assert \
                isinstance(value, Image), \
                "The 'pose_image' field must be a sub message of type 'Image'"
        self._pose_image = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_DetectPointing_Event(type):
    """Metaclass of message 'DetectPointing_Event'."""

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
            module = import_type_support('human_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'human_interfaces.srv.DetectPointing_Event')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__detect_pointing__event
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__detect_pointing__event
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__detect_pointing__event
            cls._TYPE_SUPPORT = module.type_support_msg__srv__detect_pointing__event
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__detect_pointing__event

            from service_msgs.msg import ServiceEventInfo
            if ServiceEventInfo.__class__._TYPE_SUPPORT is None:
                ServiceEventInfo.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class DetectPointing_Event(metaclass=Metaclass_DetectPointing_Event):
    """Message class 'DetectPointing_Event'."""

    __slots__ = [
        '_info',
        '_request',
        '_response',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'info': 'service_msgs/ServiceEventInfo',
        'request': 'sequence<human_interfaces/DetectPointing_Request, 1>',
        'response': 'sequence<human_interfaces/DetectPointing_Response, 1>',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['service_msgs', 'msg'], 'ServiceEventInfo'),  # noqa: E501
        rosidl_parser.definition.BoundedSequence(rosidl_parser.definition.NamespacedType(['human_interfaces', 'srv'], 'DetectPointing_Request'), 1),  # noqa: E501
        rosidl_parser.definition.BoundedSequence(rosidl_parser.definition.NamespacedType(['human_interfaces', 'srv'], 'DetectPointing_Response'), 1),  # noqa: E501
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
        from service_msgs.msg import ServiceEventInfo
        self.info = kwargs.get('info', ServiceEventInfo())
        self.request = kwargs.get('request', [])
        self.response = kwargs.get('response', [])

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
        if self.info != other.info:
            return False
        if self.request != other.request:
            return False
        if self.response != other.response:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def info(self):
        """Message field 'info'."""
        return self._info

    @info.setter
    def info(self, value):
        if self._check_fields:
            from service_msgs.msg import ServiceEventInfo
            assert \
                isinstance(value, ServiceEventInfo), \
                "The 'info' field must be a sub message of type 'ServiceEventInfo'"
        self._info = value

    @builtins.property
    def request(self):
        """Message field 'request'."""
        return self._request

    @request.setter
    def request(self, value):
        if self._check_fields:
            from human_interfaces.srv import DetectPointing_Request
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) <= 1 and
                 all(isinstance(v, DetectPointing_Request) for v in value) and
                 True), \
                "The 'request' field must be a set or sequence with length <= 1 and each value of type 'DetectPointing_Request'"
        self._request = value

    @builtins.property
    def response(self):
        """Message field 'response'."""
        return self._response

    @response.setter
    def response(self, value):
        if self._check_fields:
            from human_interfaces.srv import DetectPointing_Response
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) <= 1 and
                 all(isinstance(v, DetectPointing_Response) for v in value) and
                 True), \
                "The 'response' field must be a set or sequence with length <= 1 and each value of type 'DetectPointing_Response'"
        self._response = value


class Metaclass_DetectPointing(type):
    """Metaclass of service 'DetectPointing'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('human_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'human_interfaces.srv.DetectPointing')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__detect_pointing

            from human_interfaces.srv import _detect_pointing
            if _detect_pointing.Metaclass_DetectPointing_Request._TYPE_SUPPORT is None:
                _detect_pointing.Metaclass_DetectPointing_Request.__import_type_support__()
            if _detect_pointing.Metaclass_DetectPointing_Response._TYPE_SUPPORT is None:
                _detect_pointing.Metaclass_DetectPointing_Response.__import_type_support__()
            if _detect_pointing.Metaclass_DetectPointing_Event._TYPE_SUPPORT is None:
                _detect_pointing.Metaclass_DetectPointing_Event.__import_type_support__()


class DetectPointing(metaclass=Metaclass_DetectPointing):
    from human_interfaces.srv._detect_pointing import DetectPointing_Request as Request
    from human_interfaces.srv._detect_pointing import DetectPointing_Response as Response
    from human_interfaces.srv._detect_pointing import DetectPointing_Event as Event

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
