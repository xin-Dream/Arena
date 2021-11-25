// Generated by gencpp from file ros_stm32_bridge/stm32_motor.msg
// DO NOT EDIT!


#ifndef ROS_STM32_BRIDGE_MESSAGE_STM32_MOTOR_H
#define ROS_STM32_BRIDGE_MESSAGE_STM32_MOTOR_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace ros_stm32_bridge
{
template <class ContainerAllocator>
struct stm32_motor_
{
  typedef stm32_motor_<ContainerAllocator> Type;

  stm32_motor_()
    : pitch(0.0)
    , yaw(0.0)
    , roll(0.0)  {
    }
  stm32_motor_(const ContainerAllocator& _alloc)
    : pitch(0.0)
    , yaw(0.0)
    , roll(0.0)  {
  (void)_alloc;
    }



   typedef double _pitch_type;
  _pitch_type pitch;

   typedef double _yaw_type;
  _yaw_type yaw;

   typedef double _roll_type;
  _roll_type roll;





  typedef boost::shared_ptr< ::ros_stm32_bridge::stm32_motor_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ros_stm32_bridge::stm32_motor_<ContainerAllocator> const> ConstPtr;

}; // struct stm32_motor_

typedef ::ros_stm32_bridge::stm32_motor_<std::allocator<void> > stm32_motor;

typedef boost::shared_ptr< ::ros_stm32_bridge::stm32_motor > stm32_motorPtr;
typedef boost::shared_ptr< ::ros_stm32_bridge::stm32_motor const> stm32_motorConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ros_stm32_bridge::stm32_motor_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ros_stm32_bridge::stm32_motor_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::ros_stm32_bridge::stm32_motor_<ContainerAllocator1> & lhs, const ::ros_stm32_bridge::stm32_motor_<ContainerAllocator2> & rhs)
{
  return lhs.pitch == rhs.pitch &&
    lhs.yaw == rhs.yaw &&
    lhs.roll == rhs.roll;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::ros_stm32_bridge::stm32_motor_<ContainerAllocator1> & lhs, const ::ros_stm32_bridge::stm32_motor_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace ros_stm32_bridge

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::ros_stm32_bridge::stm32_motor_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ros_stm32_bridge::stm32_motor_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ros_stm32_bridge::stm32_motor_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ros_stm32_bridge::stm32_motor_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ros_stm32_bridge::stm32_motor_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ros_stm32_bridge::stm32_motor_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ros_stm32_bridge::stm32_motor_<ContainerAllocator> >
{
  static const char* value()
  {
    return "6b33b81f528b84606cf372e61b6ef5ea";
  }

  static const char* value(const ::ros_stm32_bridge::stm32_motor_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x6b33b81f528b8460ULL;
  static const uint64_t static_value2 = 0x6cf372e61b6ef5eaULL;
};

template<class ContainerAllocator>
struct DataType< ::ros_stm32_bridge::stm32_motor_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ros_stm32_bridge/stm32_motor";
  }

  static const char* value(const ::ros_stm32_bridge::stm32_motor_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ros_stm32_bridge::stm32_motor_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 pitch\n"
"float64 yaw\n"
"float64 roll\n"
;
  }

  static const char* value(const ::ros_stm32_bridge::stm32_motor_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ros_stm32_bridge::stm32_motor_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.pitch);
      stream.next(m.yaw);
      stream.next(m.roll);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct stm32_motor_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ros_stm32_bridge::stm32_motor_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ros_stm32_bridge::stm32_motor_<ContainerAllocator>& v)
  {
    s << indent << "pitch: ";
    Printer<double>::stream(s, indent + "  ", v.pitch);
    s << indent << "yaw: ";
    Printer<double>::stream(s, indent + "  ", v.yaw);
    s << indent << "roll: ";
    Printer<double>::stream(s, indent + "  ", v.roll);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROS_STM32_BRIDGE_MESSAGE_STM32_MOTOR_H
