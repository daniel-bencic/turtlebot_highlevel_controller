#include "../include/turtlebot_highlevel_controller/cartesian_point.h"

namespace turtlebot_highlevel_controller {
        CartesianPoint::CartesianPoint() : CartesianPoint(0.0f, 0.0f, 0.0f, 0.0f) {}

        CartesianPoint::CartesianPoint(float x, float y) : CartesianPoint(x, y, 0.0f, 0.0f) {}

        CartesianPoint::CartesianPoint(float x, float y, float z) : CartesianPoint(x, y, z, 0.0f) {}

        CartesianPoint::CartesianPoint(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
}

