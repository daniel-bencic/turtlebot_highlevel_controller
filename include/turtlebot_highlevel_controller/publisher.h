#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <string>

#include <ros/ros.h>

namespace turtlebot_highlevel_controller {
        template <typename T>
        class Publisher {
                public:
                        Publisher();
                        Publisher(ros::NodeHandle& nh,
                                  const std::string& topic,
                                  uint32_t queue_size);
                        ~Publisher();
                        void publish(const T& msg) const;

                private:
                        ros::Publisher pub;
        };

        template <typename T>
        Publisher<T>::Publisher() {}

        template <typename T>
        Publisher<T>::Publisher(ros::NodeHandle& nh,
                                const std::string& topic,
                                uint32_t queue_size)
        {
                this->pub = nh.advertise<T>(topic, queue_size);
                if (!this->pub) {
                        ROS_FATAL_STREAM("Advertising topic [" << topic << "]: failed!");
                }
        }

        template <typename T>
        Publisher<T>::~Publisher<T>() {}

        template <typename T>
        void Publisher<T>::publish(const T& msg) const
        {
             this->pub.publish(msg);   
        }
}

#endif /* PUBLISHER_H */
