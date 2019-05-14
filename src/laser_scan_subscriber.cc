#include "../include/turtlebot_highlevel_controller/laser_scan_subscriber.h"
#include "../include/turtlebot_highlevel_controller/algorithm/laser_scan_util.h"

namespace turtlebot_highlevel_controller {
        sensor_msgs::LaserScan g_latest_scan;
        
        LaserScanSubscriber::LaserScanSubscriber() {}

        LaserScanSubscriber::LaserScanSubscriber(
                                                ros::NodeHandle& nh,
                                                const std::string& topic,
                                                uint32_t queue_size
                                                )
        {
                this->sub = nh.subscribe(topic, queue_size,
                                         &LaserScanSubscriber::callback,
                                         this);
                if (!this->sub) {
                        ROS_FATAL_STREAM("Subscribing to topic [" << topic << "]: failed!");
                }
        }

        LaserScanSubscriber::~LaserScanSubscriber() {}

        void LaserScanSubscriber::callback(const sensor_msgs::LaserScan& msg)
        {
                sensor_msgs::LaserScan scan = msg;
                g_latest_scan = scan;
                ROS_INFO_STREAM("Smallest range: " << util::smallest_range(scan.ranges));
        }
}
