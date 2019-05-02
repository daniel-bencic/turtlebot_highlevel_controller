#include "../include/turtlebot_highlevel_controller/laser_scan_subscriber.h"
#include "../include/turtlebot_highlevel_controller/algorithm/laser_scan_util.h"

namespace turtlebot_highlevel_controller {
        sensor_msgs::LaserScan l;
        
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
        
        sensor_msgs::LaserScan LaserScanSubscriber::get_latest_scan() const
        {
                return this->latest_scan;
        }

        void LaserScanSubscriber::callback(const sensor_msgs::LaserScan& msg)
        {
                sensor_msgs::LaserScan scan = msg;
                l = scan;
                ROS_INFO_STREAM("Smallest range: " << util::smallest_dist(scan));
        }
}
