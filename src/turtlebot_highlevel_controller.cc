#include "../include/turtlebot_highlevel_controller/turtlebot_highlevel_controller.h"
#include "../include/turtlebot_highlevel_controller/parameter_accessor.h"
#include "../include/turtlebot_highlevel_controller/algorithm/laser_scan_util.h"

namespace turtlebot_highlevel_controller
{
        TurtlebotHighlevelController::TurtlebotHighlevelController(ros::NodeHandle& nh) 
        {
                ParameterAccessor pa(nh);
                std::string sub_topic = pa.get_parameter<std::string>("/turtlebot_highlevel_controller/sub_topic");
                std::string pub_topic = pa.get_parameter<std::string>("/turtlebot_highlevel_controller/pub_topic");
                int queue_size = pa.get_parameter<int>("/turtlebot_highlevel_controller/queue_size");
                

                this->laser_scan_sub = 
                        LaserScanSubscriber(nh, sub_topic, queue_size);

                this->laser_scan_pub =
                        LaserScanPublisher(nh, pub_topic, queue_size);
        }

        TurtlebotHighlevelController::~TurtlebotHighlevelController() {}

        void TurtlebotHighlevelController::publish_filtered_laser_scan()
        {
                sensor_msgs::LaserScan filtered_scan = util::filter_scan(g_latest_scan);
                this->laser_scan_pub.publish(filtered_scan);
        }
}
