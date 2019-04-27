#ifndef TOPIC_SUBSCRIBER_LASER_SCAN_H
#define TOPIC_SUBSCRIBER_LASER_SCAN_H

#include <string>

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

namespace thc {
        class topic_subscriber_laser_scan {
                public:
                        topic_subscriber_laser_scan();
                        topic_subscriber_laser_scan(ros::NodeHandle& nh,
                                                    const std::string& topic,
                                                    uint32_t queue_size);
                        ~topic_subscriber_laser_scan();

                private:
                        ros::Subscriber sub;
                        void callback(const sensor_msgs::LaserScan& msg);
        };
}

#endif
