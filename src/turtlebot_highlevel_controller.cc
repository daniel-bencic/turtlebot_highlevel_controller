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
                int queue_size = pa.get_parameter<int>("/turtlebot_highlevel_controller/queue_size");
                
                this->laser_scan_sub = 
                        LaserScanSubscriber(nh, s_sub_topic, queue_size);

                this->laser_scan_pub =
                        Publisher<sensor_msgs::LaserScan>(nh, fs_pub_topic, queue_size);

                this->twist_pub =
                        Publisher<geometry_msgs::Twist>(nh, t_pub_topic, queue_size);
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
}
