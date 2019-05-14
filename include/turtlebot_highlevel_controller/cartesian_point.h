namespace turtlebot_highlevel_controller {
        struct CartesianPoint {
                CartesianPoint();
                CartesianPoint(float x, float y);
                CartesianPoint(float x, float y, float z);
                CartesianPoint(float x, float y, float z, float w);

                float x, y, z, w;
        };
}
