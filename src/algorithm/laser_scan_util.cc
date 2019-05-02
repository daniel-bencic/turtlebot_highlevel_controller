#include <algorithm>

#include "../../include/turtlebot_highlevel_controller/algorithm/laser_scan_util.h"
#include <ros/ros.h>

namespace turtlebot_highlevel_controller {
        namespace util {
                float smallest_dist(sensor_msgs::LaserScan& scan)
                {
                        std::vector<float>::iterator it = std::min_element(std::begin(scan.ranges), std::end(scan.ranges));
                        return *it;
                }

                sensor_msgs::LaserScan filter_scan(sensor_msgs::LaserScan& scan)
                {
                        if (scan.ranges.empty()) return scan;

                        sensor_msgs::LaserScan f_scan = scan;
                        std::vector<float>::iterator itrb = std::begin(f_scan.ranges);
                        std::vector<float>::iterator itre = std::end(f_scan.ranges);
                        std::vector<float>::iterator itrm = std::min_element(itrb, itre);
                        std::vector<float>::iterator itib = std::begin(f_scan.intensities);
                        std::vector<float>::iterator itie = std::end(f_scan.intensities);
                        std::vector<float>::iterator itim = std::min_element(itib, itie);                                               
                        
                        std::vector<float>::iterator itfrb;
                        std::vector<float>::iterator itfib;
                        if (itrm - itrb > 1) {
                                itfrb = itrm - 2;
                                itfib = itim - 2;
                        } else {
                                itfrb = itrm - (itrm - itrb);
                                itfib = itim - (itim - itib);
                        }

                        std::vector<float>::iterator itfre;
                        std::vector<float>::iterator itfie;
                        if (itre - itrm > 1) {
                                itfre = itrm + 2;
                                itfie = itim + 2;
                        } else {
                                itfre = itrm + (itre - itrm);
                                itfie = itim + (itie - itim);
                        }

                        f_scan.ranges = std::vector<float>(itfrb, itfre + 1);
                        f_scan.intensities = std::vector<float>(itfib, itfie + 1);
                        f_scan.angle_min = f_scan.angle_min + (itfrb - itrb) * f_scan.angle_increment;
                        f_scan.angle_max = f_scan.angle_max - (itre - itfre - 1) * f_scan.angle_increment;
                        return f_scan;
                }
        }
}
