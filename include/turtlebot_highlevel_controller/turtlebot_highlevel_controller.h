#ifndef TURTLEBOT_HIGHLEVEL_CONTROLLER_H
#define TURTLEBOT_HIGHLEVEL_CONTROLLER_H

#include <std_msgs/String.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>

#include "./laser_scan_subscriber.h"
#include "./publisher.h"

namespace turtlebot_highlevel_controller
{
        /*
         * Main class of this package.
         */
        class TurtlebotHighlevelController
        {
                public:
                        TurtlebotHighlevelController(ros::NodeHandle& nh);
                        ~TurtlebotHighlevelController();
                        void publish_filtered_laser_scan();
                        void find_pillar();
                        void publish_pillar_marker();

                private:
                        LaserScanSubscriber laser_scan_sub;
                        Publisher<sensor_msgs::LaserScan> laser_scan_pub;
                        Publisher<geometry_msgs::Twist> twist_pub;
                        Publisher<visualization_msgs::Marker> marker_pub;
        };
}

#endif /* TURTLEBOT_HIGHLEVEL_CONTROLLER_H */


