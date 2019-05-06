#ifndef TURTLEBOT_HIGHLEVEL_CONTROLLER_H
#define TURTLEBOT_HIGHLEVEL_CONTROLLER_H

#include <std_msgs/String.h>

#include "./laser_scan_subscriber.h"
#include "./laser_scan_publisher.h"

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

                private:
                        LaserScanSubscriber laser_scan_sub;
                        LaserScanPublisher laser_scan_pub;
        };
}

#endif /* TURTLEBOT_HIGHLEVEL_CONTROLLER_H */


