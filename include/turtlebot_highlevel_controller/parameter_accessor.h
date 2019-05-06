#ifndef PARAMETER_ACCESSOR_H
#define PARAMETER_ACCESSOR_H

#include <string>

#include <ros/ros.h>

namespace turtlebot_highlevel_controller {
        /*
         * Class for accessing the ROS parameter server.
         */
        class ParameterAccessor {
                public:
                        ParameterAccessor(ros::NodeHandle& nh);
                        ~ParameterAccessor();
                        
                        template <typename T>
                        T get_parameter(const std::string& name) const;

                private:
                        ros::NodeHandle nh;
        };

        ParameterAccessor::ParameterAccessor(ros::NodeHandle& nh) : nh(nh) {}

        ParameterAccessor::~ParameterAccessor() {}

        template <typename T>
        T ParameterAccessor::get_parameter(const std::string& name) const
        {
                T val;
                if (!this->nh.getParam(name, val)) {
                        ROS_ERROR_STREAM("Retrieving value for parameter [" << name << "]: failed!");
                }
                return val;
        }
}

#endif /* PARAMETER_ACCESSOR_H */
