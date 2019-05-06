#ifndef TOPIC_SUBSCRIBER_LASER_SCAN_H
#define TOPIC_SUBSCRIBER_LASER_SCAN_H

#include <string>

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

namespace turtlebot_highlevel_controller {      
        extern sensor_msgs::LaserScan g_latest_scan;

        /*
         * Class for subscribing to topics, publishing
         * LaserScan messages.
         * http://docs.ros.org/melodic/api/sensor_msgs/html/msg/LaserScan.html
         */
        class LaserScanSubscriber {
                public:
                        LaserScanSubscriber();
                        LaserScanSubscriber(ros::NodeHandle& nh,
                                            const std::string& topic,
                                            uint32_t queue_size);
                        ~LaserScanSubscriber();

                private:
                        void callback(const sensor_msgs::LaserScan& msg);
                        ros::Subscriber sub;
        };
}

#endif /* TOPIC_SUBSCRIBER_LASER_SCAN_H */

