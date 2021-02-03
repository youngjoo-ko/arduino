#ifndef _ROS_object_detection_gl_ros_obj_array_h
#define _ROS_object_detection_gl_ros_obj_array_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "object_detection_gl_ros/obj_position.h"

namespace object_detection_gl_ros
{

  class obj_array : public ros::Msg
  {
    public:
      uint32_t xy_length;
      typedef object_detection_gl_ros::obj_position _xy_type;
      _xy_type st_xy;
      _xy_type * xy;

    obj_array():
      xy_length(0), st_xy(), xy(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->xy_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->xy_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->xy_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->xy_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->xy_length);
      for( uint32_t i = 0; i < xy_length; i++){
      offset += this->xy[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t xy_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      xy_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      xy_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      xy_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->xy_length);
      if(xy_lengthT > xy_length)
        this->xy = (object_detection_gl_ros::obj_position*)realloc(this->xy, xy_lengthT * sizeof(object_detection_gl_ros::obj_position));
      xy_length = xy_lengthT;
      for( uint32_t i = 0; i < xy_length; i++){
      offset += this->st_xy.deserialize(inbuffer + offset);
        memcpy( &(this->xy[i]), &(this->st_xy), sizeof(object_detection_gl_ros::obj_position));
      }
     return offset;
    }

    virtual const char * getType() override { return "object_detection_gl_ros/obj_array"; };
    virtual const char * getMD5() override { return "3e45e8a669ac07ed2cb1ae4fd47636f9"; };

  };

}
#endif
