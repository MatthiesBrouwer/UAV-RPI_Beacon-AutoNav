// Generated by gencpp from file uwb_localization_description/uwb_data_raw.msg
// DO NOT EDIT!


#ifndef UWB_LOCALIZATION_DESCRIPTION_MESSAGE_UWB_DATA_RAW_H
#define UWB_LOCALIZATION_DESCRIPTION_MESSAGE_UWB_DATA_RAW_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace uwb_localization_description
{
template <class ContainerAllocator>
struct uwb_data_raw_
{
  typedef uwb_data_raw_<ContainerAllocator> Type;

  uwb_data_raw_()
    : destination_id()
    , distance()
    , stamp()  {
    }
  uwb_data_raw_(const ContainerAllocator& _alloc)
    : destination_id(_alloc)
    , distance(_alloc)
    , stamp(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<int64_t, typename ContainerAllocator::template rebind<int64_t>::other >  _destination_id_type;
  _destination_id_type destination_id;

   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _distance_type;
  _distance_type distance;

   typedef std::vector<ros::Time, typename ContainerAllocator::template rebind<ros::Time>::other >  _stamp_type;
  _stamp_type stamp;





  typedef boost::shared_ptr< ::uwb_localization_description::uwb_data_raw_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::uwb_localization_description::uwb_data_raw_<ContainerAllocator> const> ConstPtr;

}; // struct uwb_data_raw_

typedef ::uwb_localization_description::uwb_data_raw_<std::allocator<void> > uwb_data_raw;

typedef boost::shared_ptr< ::uwb_localization_description::uwb_data_raw > uwb_data_rawPtr;
typedef boost::shared_ptr< ::uwb_localization_description::uwb_data_raw const> uwb_data_rawConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::uwb_localization_description::uwb_data_raw_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::uwb_localization_description::uwb_data_raw_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::uwb_localization_description::uwb_data_raw_<ContainerAllocator1> & lhs, const ::uwb_localization_description::uwb_data_raw_<ContainerAllocator2> & rhs)
{
  return lhs.destination_id == rhs.destination_id &&
    lhs.distance == rhs.distance &&
    lhs.stamp == rhs.stamp;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::uwb_localization_description::uwb_data_raw_<ContainerAllocator1> & lhs, const ::uwb_localization_description::uwb_data_raw_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace uwb_localization_description

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::uwb_localization_description::uwb_data_raw_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::uwb_localization_description::uwb_data_raw_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::uwb_localization_description::uwb_data_raw_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::uwb_localization_description::uwb_data_raw_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::uwb_localization_description::uwb_data_raw_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::uwb_localization_description::uwb_data_raw_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::uwb_localization_description::uwb_data_raw_<ContainerAllocator> >
{
  static const char* value()
  {
    return "853a584c8bd9fd74a6b2709e39029b14";
  }

  static const char* value(const ::uwb_localization_description::uwb_data_raw_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x853a584c8bd9fd74ULL;
  static const uint64_t static_value2 = 0xa6b2709e39029b14ULL;
};

template<class ContainerAllocator>
struct DataType< ::uwb_localization_description::uwb_data_raw_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uwb_localization_description/uwb_data_raw";
  }

  static const char* value(const ::uwb_localization_description::uwb_data_raw_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::uwb_localization_description::uwb_data_raw_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int64[] destination_id\n"
"float64[] distance\n"
"time[] stamp\n"
;
  }

  static const char* value(const ::uwb_localization_description::uwb_data_raw_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::uwb_localization_description::uwb_data_raw_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.destination_id);
      stream.next(m.distance);
      stream.next(m.stamp);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct uwb_data_raw_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::uwb_localization_description::uwb_data_raw_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::uwb_localization_description::uwb_data_raw_<ContainerAllocator>& v)
  {
    s << indent << "destination_id[]" << std::endl;
    for (size_t i = 0; i < v.destination_id.size(); ++i)
    {
      s << indent << "  destination_id[" << i << "]: ";
      Printer<int64_t>::stream(s, indent + "  ", v.destination_id[i]);
    }
    s << indent << "distance[]" << std::endl;
    for (size_t i = 0; i < v.distance.size(); ++i)
    {
      s << indent << "  distance[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.distance[i]);
    }
    s << indent << "stamp[]" << std::endl;
    for (size_t i = 0; i < v.stamp.size(); ++i)
    {
      s << indent << "  stamp[" << i << "]: ";
      Printer<ros::Time>::stream(s, indent + "  ", v.stamp[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // UWB_LOCALIZATION_DESCRIPTION_MESSAGE_UWB_DATA_RAW_H
