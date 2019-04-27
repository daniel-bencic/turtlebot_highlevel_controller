#include "../include/turtlebot_highlevel_controller/topic_subscriber_laser_scan.h"

namespace thc {
        topic_subscriber_laser_scan::topic_subscriber_laser_scan() {}

        topic_subscriber_laser_scan::topic_subscriber_laser_scan(
                                                ros::NodeHandle& nh,
                                                const std::string& topic,
                                                uint32_t queue_size
                                                )
        {
                this->sub = nh.subscribe(topic, queue_size,
                                         &topic_subscriber_laser_scan::callback,
                                         this);
                if (!this->sub) {
                        ROS_FATAL_STREAM("Subscribing to topic [" << topic << "]: failed!");
                }
        }

        topic_subscriber_laser_scan::~topic_subscriber_laser_scan() {}

        void topic_subscriber_laser_scan::callback(const sensor_msgs::LaserScan& msg)
        {
                ROS_INFO_STREAM("I heard: " << msg.scan_time);
        }
}
