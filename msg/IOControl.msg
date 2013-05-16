# This represents an input/output control structure for a Maxon motor attached to an EPOS 2 controller.  
# The node_id is the node_id set on the epos controller itself
# The state corresponds with the desired state of the digital outputs.

# State Options
uint8 ON =1
uint8 OFF = 0


uint16 node_id
uint8 state




