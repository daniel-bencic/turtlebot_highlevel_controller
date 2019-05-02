#include <sensor_msgs/LaserScan.h>

namespace turtlebot_highlevel_controller {
        namespace util {
                float smallest_dist(sensor_msgs::LaserScan& scan);
                sensor_msgs::LaserScan filter_scan(sensor_msgs::LaserScan& scan);
        }
}
