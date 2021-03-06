"""autogenerated by genpy from EposManager/IOControl.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class IOControl(genpy.Message):
  _md5sum = "df6086f1bf4654fd8c2ebfd3ebc6eec9"
  _type = "EposManager/IOControl"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """# This represents an input/output control structure for a Maxon motor attached to an EPOS 2 controller.  
# The node_id is the node_id set on the epos controller itself
# The state corresponds with the desired state of the digital outputs.

# State Options
uint8 ON =1
uint8 OFF = 0


uint16 node_id
uint8 state





"""
  # Pseudo-constants
  ON = 1
  OFF = 0

  __slots__ = ['node_id','state']
  _slot_types = ['uint16','uint8']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       node_id,state

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(IOControl, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.node_id is None:
        self.node_id = 0
      if self.state is None:
        self.state = 0
    else:
      self.node_id = 0
      self.state = 0

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
      _x = self
      buff.write(_struct_HB.pack(_x.node_id, _x.state))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 3
      (_x.node_id, _x.state,) = _struct_HB.unpack(str[start:end])
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
      _x = self
      buff.write(_struct_HB.pack(_x.node_id, _x.state))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 3
      (_x.node_id, _x.state,) = _struct_HB.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_HB = struct.Struct("<HB")
