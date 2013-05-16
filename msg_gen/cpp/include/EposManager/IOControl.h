/* Auto-generated by genmsg_cpp for file /home/ttremblay/groovy_workspace/sandbox/EposManager/msg/IOControl.msg */
#ifndef EPOSMANAGER_MESSAGE_IOCONTROL_H
#define EPOSMANAGER_MESSAGE_IOCONTROL_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace EposManager
{
template <class ContainerAllocator>
struct IOControl_ {
  typedef IOControl_<ContainerAllocator> Type;

  IOControl_()
  : node_id(0)
  , state(0)
  {
  }

  IOControl_(const ContainerAllocator& _alloc)
  : node_id(0)
  , state(0)
  {
  }

  typedef uint16_t _node_id_type;
  uint16_t node_id;

  typedef uint8_t _state_type;
  uint8_t state;

  enum { ON = 1 };
  enum { OFF = 0 };

  typedef boost::shared_ptr< ::EposManager::IOControl_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::EposManager::IOControl_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct IOControl
typedef  ::EposManager::IOControl_<std::allocator<void> > IOControl;

typedef boost::shared_ptr< ::EposManager::IOControl> IOControlPtr;
typedef boost::shared_ptr< ::EposManager::IOControl const> IOControlConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::EposManager::IOControl_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::EposManager::IOControl_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace EposManager

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::EposManager::IOControl_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::EposManager::IOControl_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::EposManager::IOControl_<ContainerAllocator> > {
  static const char* value() 
  {
    return "df6086f1bf4654fd8c2ebfd3ebc6eec9";
  }

  static const char* value(const  ::EposManager::IOControl_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xdf6086f1bf4654fdULL;
  static const uint64_t static_value2 = 0x8c2ebfd3ebc6eec9ULL;
};

template<class ContainerAllocator>
struct DataType< ::EposManager::IOControl_<ContainerAllocator> > {
  static const char* value() 
  {
    return "EposManager/IOControl";
  }

  static const char* value(const  ::EposManager::IOControl_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::EposManager::IOControl_<ContainerAllocator> > {
  static const char* value() 
  {
    return "# This represents an input/output control structure for a Maxon motor attached to an EPOS 2 controller.  \n\
# The node_id is the node_id set on the epos controller itself\n\
# The state corresponds with the desired state of the digital outputs.\n\
\n\
# State Options\n\
uint8 ON =1\n\
uint8 OFF = 0\n\
\n\
\n\
uint16 node_id\n\
uint8 state\n\
\n\
\n\
\n\
\n\
\n\
";
  }

  static const char* value(const  ::EposManager::IOControl_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::EposManager::IOControl_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::EposManager::IOControl_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.node_id);
    stream.next(m.state);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct IOControl_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::EposManager::IOControl_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::EposManager::IOControl_<ContainerAllocator> & v) 
  {
    s << indent << "node_id: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.node_id);
    s << indent << "state: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.state);
  }
};


} // namespace message_operations
} // namespace ros

#endif // EPOSMANAGER_MESSAGE_IOCONTROL_H

