#ifndef LASER_SCAN_UTIL_H
#define LASER_SCAN_UTIL_H

#include <vector>

#include <sensor_msgs/LaserScan.h>

namespace turtlebot_highlevel_controller {
        /*
         * Utility functions for LaserScan messages.
         */
        namespace util {
                float smallest_range(std::vector<float>& ranges);
                sensor_msgs::LaserScan filter_scan(sensor_msgs::LaserScan& scan);
                bool obstacle_detected(std::vector<float>& intensities);
                std::vector<float> polar_to_cartesian(std::vector<float>& coords);
        }
}

#endif /* LASER_SCAN_UTIL_H */
