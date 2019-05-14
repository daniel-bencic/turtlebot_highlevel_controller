#include "../include/turtlebot_highlevel_controller/turtlebot_highlevel_controller.h"
#include "../include/turtlebot_highlevel_controller/parameter_accessor.h"
#include "../include/turtlebot_highlevel_controller/algorithm/laser_scan_util.h"

namespace turtlebot_highlevel_controller
{
        TurtlebotHighlevelController::TurtlebotHighlevelController(ros::NodeHandle& nh) 
        {
                ParameterAccessor pa(nh);
                std::string s_sub_topic = pa.get_parameter<std::string>("/turtlebot_highlevel_controller/scan_sub_topic");
                std::string fs_pub_topic = pa.get_parameter<std::string>("/turtlebot_highlevel_controller/filtered_scan_pub_topic");
                std::string t_pub_topic = pa.get_parameter<std::string>("/turtlebot_highlevel_controller/twist_pub_topic");
                std::string m_pub_topic = pa.get_parameter<std::string>("/turtlebot_highlevel_controller/marker_pub_topic");
                int queue_size = pa.get_parameter<int>("/turtlebot_highlevel_controller/queue_size");
                
                this->laser_scan_sub = 
                        LaserScanSubscriber(nh, s_sub_topic, queue_size);

                this->laser_scan_pub =
                        Publisher<sensor_msgs::LaserScan>(nh, fs_pub_topic, queue_size);

                this->twist_pub =
                        Publisher<geometry_msgs::Twist>(nh, t_pub_topic, queue_size);

                this->marker_pub =
                        Publisher<visualization_msgs::Marker>(nh, m_pub_topic, queue_size);
        }

        TurtlebotHighlevelController::~TurtlebotHighlevelController() {}

        void TurtlebotHighlevelController::publish_filtered_laser_scan()
        {
                sensor_msgs::LaserScan filtered_scan = util::filter_scan(g_latest_scan);
                this->laser_scan_pub.publish(filtered_scan);
        }

        void TurtlebotHighlevelController::find_pillar()
        {
                geometry_msgs::Twist t;

                if (util::obstacle_detected(g_latest_scan.intensities))
                        t.angular.z = 2.0f;

                this->twist_pub.publish(t);
        }

        void TurtlebotHighlevelController::publish_pillar_marker()
        {
                visualization_msgs::Marker marker;
                marker.header.frame_id = "base_laser_link";
                marker.header.stamp = ros::Time();
                marker.ns = "turtlebot_highlevel_controller";
                marker.id = 0;
                marker.type = visualization_msgs::Marker::CYLINDER;
                marker.action = visualization_msgs::Marker::ADD;

                PolarPoint pp = util::closest_point(g_latest_scan.ranges, g_latest_scan.angle_min, g_latest_scan.angle_increment);
                CartesianPoint cp = util::polar_to_cartesian(pp);
                marker.pose.position.x = cp.x;
                marker.pose.position.y = cp.y;
                marker.pose.position.z = 0.0f;
                marker.pose.orientation.x = 0.0f;
                marker.pose.orientation.y = 0.0f;
                marker.pose.orientation.z = 0.0f;
                marker.pose.orientation.w = 1.0f;
                marker.scale.x = 0.5f;
                marker.scale.y = 0.5f;
                marker.scale.z = 0.5f;
                marker.color.r = 5.0f;
                marker.color.g = 0.0f;
                marker.color.b = 0.0f;
                marker.color.a = 0.8f;

                this->marker_pub.publish(marker);
        }
}
