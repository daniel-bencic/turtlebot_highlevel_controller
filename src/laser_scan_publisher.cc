#include "../include/turtlebot_highlevel_controller/laser_scan_publisher.h"

namespace turtlebot_highlevel_controller {
        LaserScanPublisher::LaserScanPublisher() {}

        LaserScanPublisher::LaserScanPublisher(ros::NodeHandle nh,
                                               const std::string& topic,
                                               uint32_t queue_size)
        {
                this->pub = nh.advertise<sensor_msgs::LaserScan>(topic, queue_size);
                if (!this->pub) {
                        ROS_FATAL_STREAM("Advertising topic [" << topic << "]: failed!");
                }
        }

        LaserScanPublisher::~LaserScanPublisher() {}

        void LaserScanPublisher::publish(const sensor_msgs::LaserScan& scan) const
        {
                this->pub.publish(scan);
        }
}
