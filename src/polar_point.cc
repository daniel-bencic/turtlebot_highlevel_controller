#include "../include/turtlebot_highlevel_controller/polar_point.h"

namespace turtlebot_highlevel_controller {
        PolarPoint::PolarPoint() : PolarPoint(0.0f, 0.0f) {}

        PolarPoint::PolarPoint(float dist, float angle) : dist(dist), angle(angle) {}
}
