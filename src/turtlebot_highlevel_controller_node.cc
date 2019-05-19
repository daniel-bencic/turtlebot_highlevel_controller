#include <ros/ros.h>

#include "../include/turtlebot_highlevel_controller/turtlebot_highlevel_controller.h"

int main(int argc, char *argv[])
{
        ros::init(argc, argv, "turtlebot_highlevel_controller");

        turtlebot_highlevel_controller::TurtlebotHighlevelController ctrl;

        ros::Rate r(10);
        while (ros::ok()) {
                ros::spinOnce();
                ctrl.publish_filtered_laser_scan();
                ctrl.publish_pillar_marker();
                ctrl.move_to_pillar();
                r.sleep();
        }

        return 0;
}
