#include <ros/ros.h>

#include "../include/turtlebot_highlevel_controller/turtlebot_highlevel_controller.h"

int main(int argc, char *argv[])
{
        ros::init(argc, argv, "turtlebot_highlevel_controller");

        ros::NodeHandle nh("/");
        thc::turtlebot_highlevel_controller ctrl(nh);

        ros::spin();

        return 0;
}
