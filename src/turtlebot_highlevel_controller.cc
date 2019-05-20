#include "../include/turtlebot_highlevel_controller/turtlebot_highlevel_controller.h"
#include "../include/turtlebot_highlevel_controller/parameter_accessor.h"
#include "../include/turtlebot_highlevel_controller/algorithm/laser_scan_util.h"

namespace turtlebot_highlevel_controller
{
        TurtlebotHighlevelController::TurtlebotHighlevelController(ros::NodeHandle& nh, tf::TransformListener* lis) :nh(nh), lis(lis) 
        {
                ParameterAccessor pa(this->nh);
                std::string s_sub_topic = pa.get_parameter<std::string>("/turtlebot_highlevel_controller/scan_sub_topic");
                std::string fs_pub_topic = pa.get_parameter<std::string>("/turtlebot_highlevel_controller/filtered_scan_pub_topic");
                std::string t_pub_topic = pa.get_parameter<std::string>("/turtlebot_highlevel_controller/twist_pub_topic");
                std::string m_pub_topic = pa.get_parameter<std::string>("/turtlebot_highlevel_controller/marker_pub_topic");
                std::string m_t_pub_topic = pa.get_parameter<std::string>("/turtlebot_highlevel_controller/marker_transformed_pub_topic");
                int queue_size = pa.get_parameter<int>("/turtlebot_highlevel_controller/queue_size");

                this->base_linear_speed = pa.get_parameter<float>("/turtlebot_highlevel_controller/base_linear_speed");
                this->base_angular_speed = pa.get_parameter<float>("/turtlebot_highlevel_controller/base_angular_speed");
                this->p_factor = pa.get_parameter<float>("/turtlebot_highlevel_controller/p_factor");
                this->stopping_dist = pa.get_parameter<float>("/turtlebot_highlevel_controller/stopping_dist");
                this->pillar_found = false;
                
                this->laser_scan_sub = 
                        LaserScanSubscriber(nh, s_sub_topic, queue_size);

                this->laser_scan_pub =
                        Publisher<sensor_msgs::LaserScan>(nh, fs_pub_topic, queue_size);

                this->twist_pub =
                        Publisher<geometry_msgs::Twist>(nh, t_pub_topic, queue_size);

                this->marker_pub =
                        Publisher<visualization_msgs::Marker>(nh, m_pub_topic, queue_size);

                this->marker_transformed_pub =
                        Publisher<visualization_msgs::Marker>(nh, m_t_pub_topic, queue_size);
        }

        TurtlebotHighlevelController::~TurtlebotHighlevelController() {}

        void TurtlebotHighlevelController::publish_filtered_laser_scan()
        {
                sensor_msgs::LaserScan filtered_scan = util::filter_scan(g_latest_scan);
                this->laser_scan_pub.publish(filtered_scan);
        }

        void TurtlebotHighlevelController::move_to_pillar()
        {
                if (g_latest_scan.intensities.empty()) return;
                
                geometry_msgs::Twist t;

                if (!this->pillar_found) {
                        int first_hit = util::first_hit(g_latest_scan.intensities);
                        int mid = g_latest_scan.intensities.size() / 2;
                        if (first_hit > mid - 50 && first_hit < mid + 50) {
                                this->pillar_found = true;
                        } else {
                                t.angular.z = this->base_angular_speed;
                        }
                } else {
                        if (util::closest_point(g_latest_scan.ranges, g_latest_scan.angle_min, g_latest_scan.angle_increment).dist > this->stopping_dist) {
                                t.linear.x = this->base_linear_speed;
                                t.angular.z = this->adjust_movement();
                        }
                }

                this->twist_pub.publish(t);
        }

        void TurtlebotHighlevelController::publish_pillar_marker()
        {
                if (!this->pillar_found) return;

                PolarPoint pp = util::closest_point(g_latest_scan.ranges, g_latest_scan.angle_min, g_latest_scan.angle_increment);
                CartesianPoint cp = util::polar_to_cartesian(pp);
                
                geometry_msgs::Point p;
                p.x = cp.x;
                p.y = cp.y;
                p.z = cp.z;

                std_msgs::ColorRGBA color;
                color.r = 5.0f;
                color.a = 0.8f;

                this->marker_pub.publish(this->create_marker("base_laser_link", 0, p, color));
        }

        void TurtlebotHighlevelController::publish_pillar_marker_transformed()
        {
                if (!this->pillar_found) return;

                tf::StampedTransform transform;
                try {
                        (*this->lis).lookupTransform("/odom", "/base_laser_link", ros::Time(0), transform);
                } catch (tf::TransformException &ex) {
                        ROS_ERROR_STREAM("Looking up transformation: failed!\n Message: " << ex.what());
                        ros::Duration(1.0).sleep();
                }

                PolarPoint pp = util::closest_point(g_latest_scan.ranges, g_latest_scan.angle_min, g_latest_scan.angle_increment);
                CartesianPoint cp = util::polar_to_cartesian(pp);
                
                geometry_msgs::PointStamped p_in;
                p_in.header.frame_id = "base_laser_link";
                p_in.header.stamp = ros::Time(0);
                p_in.point.x = cp.x;
                p_in.point.y = cp.y;
                p_in.point.z = cp.z;

                geometry_msgs::PointStamped p_out;
                (*this->lis).transformPoint("odom", p_in, p_out);

                geometry_msgs::Point p;
                p.x = p_out.point.x;
                p.y = p_out.point.y;
                p.z = p_out.point.z;

                std_msgs::ColorRGBA color;
                color.g = 5.0f;
                color.a = 0.8f;

                this->marker_transformed_pub.publish(this->create_marker("odom", 1, p, color));
        }

        float TurtlebotHighlevelController::adjust_movement()
        {
                int error = (g_latest_scan.intensities.size() / 2) - util::first_hit(g_latest_scan.intensities);
                float adj = error * this->p_factor;
                return -adj;
        }

        visualization_msgs::Marker TurtlebotHighlevelController::create_marker(std::string frame, int id,
                                                                               geometry_msgs::Point pos,
                                                                               std_msgs::ColorRGBA color)
        {
                visualization_msgs::Marker marker;
                marker.header.frame_id = frame;
                marker.header.stamp = ros::Time();
                marker.ns = "turtlebot_highlevel_controller";
                marker.id = id;
                marker.type = visualization_msgs::Marker::CYLINDER;
                marker.action = visualization_msgs::Marker::ADD;

                marker.pose.position = pos;
                marker.pose.orientation.x = 0.0f;
                marker.pose.orientation.y = 0.0f;
                marker.pose.orientation.z = 0.0f;
                marker.pose.orientation.w = 1.0f;
                marker.scale.x = 0.5f;
                marker.scale.y = 0.5f;
                marker.scale.z = 0.5f;
                marker.color = color;

                return marker;
        }
}
