#ifndef TURTLEBOT_HIGHLEVEL_CONTROLLER_H
#define TURTLEBOT_HIGHLEVEL_CONTROLLER_H

#include <tf/transform_listener.h>
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
                        void move_to_pillar();
                        void publish_pillar_marker();
                        void publish_pillar_marker_transformed();

                private:
                        float adjust_movement();
                        visualization_msgs::Marker create_marker(std::string frame,
                                                                 int id,
                                                                 geometry_msgs::Point pos,
                                                                 std_msgs::ColorRGBA color);

                        LaserScanSubscriber laser_scan_sub;
                        Publisher<sensor_msgs::LaserScan> laser_scan_pub;
                        Publisher<geometry_msgs::Twist> twist_pub;
                        Publisher<visualization_msgs::Marker> marker_pub;
                        Publisher<visualization_msgs::Marker> marker_transformed_pub;
                        bool pillar_found;
                        float base_linear_speed;
                        float base_angular_speed;
                        float p_factor;
                        float stopping_dist;
                        ros::NodeHandle nh;
                        tf::TransformListener lis;
        };
}

#endif /* TURTLEBOT_HIGHLEVEL_CONTROLLER_H */


