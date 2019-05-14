#ifndef LASER_SCAN_UTIL_H
#define LASER_SCAN_UTIL_H

#include <vector>

#include <sensor_msgs/LaserScan.h>

#include "../cartesian_point.h"
#include "../polar_point.h"

namespace turtlebot_highlevel_controller {
        /*
         * Utility functions for LaserScan messages.
         */
        namespace util {
                PolarPoint closest_point(std::vector<float>& ranges, float angle_min, float angle_increment);
                sensor_msgs::LaserScan filter_scan(sensor_msgs::LaserScan& scan);
                bool obstacle_detected(std::vector<float>& intensities);
                CartesianPoint polar_to_cartesian(PolarPoint p);
        }
}

#endif /* LASER_SCAN_UTIL_H */
