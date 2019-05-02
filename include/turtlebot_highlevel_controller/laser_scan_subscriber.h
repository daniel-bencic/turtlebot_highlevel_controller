#ifndef TOPIC_SUBSCRIBER_LASER_SCAN_H
#define TOPIC_SUBSCRIBER_LASER_SCAN_H

#include <string>

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

namespace turtlebot_highlevel_controller {      
        extern sensor_msgs::LaserScan l;

        class LaserScanSubscriber {
                public:
                        LaserScanSubscriber();
                        LaserScanSubscriber(ros::NodeHandle& nh,
                                            const std::string& topic,
                                            uint32_t queue_size);
                        ~LaserScanSubscriber();
                        sensor_msgs::LaserScan get_latest_scan() const;

                private:
                        void callback(const sensor_msgs::LaserScan& msg);
                        ros::Subscriber sub;
                        sensor_msgs::LaserScan latest_scan;
         };
}

#endif
