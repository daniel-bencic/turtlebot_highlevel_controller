#include "../include/turtlebot_highlevel_controller/turtlebot_highlevel_controller.h"
#include "../include/turtlebot_highlevel_controller/parameter_accessor.h"

namespace thc
{
        turtlebot_highlevel_controller::turtlebot_highlevel_controller(ros::NodeHandle& nh) 
        {
                parameter_accessor pa(nh);
                this->top_sub = 
                        topic_subscriber_laser_scan(nh,
                                                    pa.get_parameter<std::string>("/turtlebot_highlevel_controller/topic"),
                                                    pa.get_parameter<int>("/turtlebot_highlevel_controller/queue_size"));
        }

        turtlebot_highlevel_controller::~turtlebot_highlevel_controller() {}
}
