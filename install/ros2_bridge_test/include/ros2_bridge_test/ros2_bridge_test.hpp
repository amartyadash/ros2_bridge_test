#pragma once

#include <memory>
#include <iostream> 
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "sensor_msgs/image_encodings.hpp"
#include <opencv2/opencv.hpp>
#include "cv_bridge/cv_bridge.h"
#include <string>
#include <sstream>
#include <vector>
#include <assert.h>

namespace ariitk::ros2_bridge_test {

class ImageSubscriber : public rclcpp::Node {
  public:
    ImageSubscriber();

  private:
    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg);
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
    cv::Mat frame_;
    cv_bridge::CvImagePtr cv_ptr_;
    std::vector<int> compression_params_;
    std::string image_name_;
    int count_, num_;
    std::string frame_id_;
};

}//ariitk::ros2_bridge_test