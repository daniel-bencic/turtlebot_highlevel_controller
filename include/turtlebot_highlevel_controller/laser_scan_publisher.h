#ifndef LASER_SCAN_PUBLISHER_H
#define LASER_SCAN_PUBLISHER_H

#include <string>

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

namespace turtlebot_highlevel_controller {
        /*
         * Class for publishing LaserScan Messages
         * http://docs.ros.org/melodic/api/sensor_msgs/html/msg/LaserScan.html
         */
        class LaserScanPublisher {
                public:
                        LaserScanPublisher();
                        LaserScanPublisher(ros::NodeHandle nh,
                                           const std::string& topic,
                                           uint32_t queue_size);
                        ~LaserScanPublisher();
                        void publish(const sensor_msgs::LaserScan& scan) const;

                private:
                        ros::Publisher pub;
        };
}

#endif /* LASER_SCAN_PUBLISHER_H */

