#ifndef TURTLEBOT_HIGHLEVEL_CONTROLLER_H
#define TURTLEBOT_HIGHLEVEL_CONTROLLER_H

#include <std_msgs/String.h>

#include "./topic_subscriber_laser_scan.h"

namespace thc
{
        class turtlebot_highlevel_controller
        {
                public:
                        turtlebot_highlevel_controller(ros::NodeHandle& nh);
                        ~turtlebot_highlevel_controller();

                private:
                        topic_subscriber_laser_scan top_sub;

        };
}

#endif /* TURTLEBOT_HIGHLEVEL_CONTROLLER_H */


