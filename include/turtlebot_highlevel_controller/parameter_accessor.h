#ifndef PARAMETER_ACCESSOR_H
#define PARAMETER_ACCESSOR_H

#include <string>

#include <ros/ros.h>

namespace thc {
        class parameter_accessor {
                public:
                        parameter_accessor(ros::NodeHandle& nh);
                        ~parameter_accessor();
                        
                        template <typename T>
                        T get_parameter(const std::string& name) const;

                private:
                        ros::NodeHandle nh;
        };

        parameter_accessor::parameter_accessor(ros::NodeHandle& nh) : nh(nh) {}

        parameter_accessor::~parameter_accessor() {}

        template <typename T>
        T parameter_accessor::get_parameter(const std::string& name) const
        {
                T val;
                if (!this->nh.getParam(name, val)) {
                        ROS_ERROR_STREAM("Retrieving value for parameter [" << name << "]: failed!");
                }
                return val;
        }
}

#endif

