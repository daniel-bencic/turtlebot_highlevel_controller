#ifndef LASER_SCAN_PUBLISHER_H
#define LASER_SCAN_PUBLISHER_H

#include <string>

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

namespace turtlebot_highlevel_controller {
        class LaserScanPublisher {
                public:
                        LaserScanPublisher();
                        LaserScanPublisher(ros::NodeHandle nh,
                                           const std::string& topic,
                                           uint32_t queue_size);
                        void publish(const sensor_msgs::LaserScan& scan) const;
                        ~LaserScanPublisher();

                private:
                        ros::Publisher pub;
        };
}

#endif
