"""autogenerated by genpy from EposManager/GroupMotorInfo.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import genpy
import EposManager.msg

class GroupMotorInfo(genpy.Message):
  _md5sum = "c8fc4a927893301f8ae92f3a694c5218"
  _type = "EposManager/GroupMotorInfo"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """# This represents the motor information of a group of motors

MotorInfo[] motor_group

================================================================================
MSG: EposManager/MotorInfo
# This represents the motor information of a specific motor
# node_id is the node_id set on the EPOS Controller itself
# motor_name is the name of the motor, as assigned by the user
# enabled indicated whether or not the motor is enabled or disabled
# motor_mode is the mode the motor is in (velocity, position, current)
# motor_velocity is the velocity of the motor in rpm
# motor_position is the position of the motor in encoder counts
# motor_current is the current on the motor in milliamps

uint16 node_id
string motor_name
uint16 state
string faults
int32 motor_velocity
int32 motor_position
int32 motor_current
uint8 digital_input_3_state
uint8 digital_input_4_state
time stamp

"""
  __slots__ = ['motor_group']
  _slot_types = ['EposManager/MotorInfo[]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       motor_group

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(GroupMotorInfo, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.motor_group is None:
        self.motor_group = []
    else:
      self.motor_group = []

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      length = len(self.motor_group)
      buff.write(_struct_I.pack(length))
      for val1 in self.motor_group:
        buff.write(_struct_H.pack(val1.node_id))
        _x = val1.motor_name
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        buff.write(_struct_H.pack(val1.state))
        _x = val1.faults
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = val1
        buff.write(_struct_3i2B.pack(_x.motor_velocity, _x.motor_position, _x.motor_current, _x.digital_input_3_state, _x.digital_input_4_state))
        _v1 = val1.stamp
        _x = _v1
        buff.write(_struct_2I.pack(_x.secs, _x.nsecs))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.motor_group is None:
        self.motor_group = None
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.motor_group = []
      for i in range(0, length):
        val1 = EposManager.msg.MotorInfo()
        start = end
        end += 2
        (val1.node_id,) = _struct_H.unpack(str[start:end])
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.motor_name = str[start:end].decode('utf-8')
        else:
          val1.motor_name = str[start:end]
        start = end
        end += 2
        (val1.state,) = _struct_H.unpack(str[start:end])
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.faults = str[start:end].decode('utf-8')
        else:
          val1.faults = str[start:end]
        _x = val1
        start = end
        end += 14
        (_x.motor_velocity, _x.motor_position, _x.motor_current, _x.digital_input_3_state, _x.digital_input_4_state,) = _struct_3i2B.unpack(str[start:end])
        _v2 = val1.stamp
        _x = _v2
        start = end
        end += 8
        (_x.secs, _x.nsecs,) = _struct_2I.unpack(str[start:end])
        self.motor_group.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      length = len(self.motor_group)
      buff.write(_struct_I.pack(length))
      for val1 in self.motor_group:
        buff.write(_struct_H.pack(val1.node_id))
        _x = val1.motor_name
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        buff.write(_struct_H.pack(val1.state))
        _x = val1.faults
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = val1
        buff.write(_struct_3i2B.pack(_x.motor_velocity, _x.motor_position, _x.motor_current, _x.digital_input_3_state, _x.digital_input_4_state))
        _v3 = val1.stamp
        _x = _v3
        buff.write(_struct_2I.pack(_x.secs, _x.nsecs))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.motor_group is None:
        self.motor_group = None
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.motor_group = []
      for i in range(0, length):
        val1 = EposManager.msg.MotorInfo()
        start = end
        end += 2
        (val1.node_id,) = _struct_H.unpack(str[start:end])
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.motor_name = str[start:end].decode('utf-8')
        else:
          val1.motor_name = str[start:end]
        start = end
        end += 2
        (val1.state,) = _struct_H.unpack(str[start:end])
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.faults = str[start:end].decode('utf-8')
        else:
          val1.faults = str[start:end]
        _x = val1
        start = end
        end += 14
        (_x.motor_velocity, _x.motor_position, _x.motor_current, _x.digital_input_3_state, _x.digital_input_4_state,) = _struct_3i2B.unpack(str[start:end])
        _v4 = val1.stamp
        _x = _v4
        start = end
        end += 8
        (_x.secs, _x.nsecs,) = _struct_2I.unpack(str[start:end])
        self.motor_group.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_3i2B = struct.Struct("<3i2B")
_struct_H = struct.Struct("<H")
_struct_2I = struct.Struct("<2I")
