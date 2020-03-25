#include <ros2_bridge_test/ros2_bridge_test.hpp>

using namespace ariitk::ros2_bridge_test;

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImageSubscriber>());
    rclcpp::shutdown();
    return 0;
}