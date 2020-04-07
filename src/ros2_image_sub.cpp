#include <ros2_bridge_test/ros2_bridge_test.hpp>

using std::placeholders::_1;

namespace ariitk::ros2_bridge_test {

ImageSubscriber::ImageSubscriber(): Node("image_subscriber") {
      subscription_ = this->create_subscription<sensor_msgs::msg::Image>("bridge_image", 20, std::bind(&ImageSubscriber::imageCallback, this, _1));
      count_ = 0;
      num_ = 40; //TODO : Convert this to param
}

void ImageSubscriber::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg) {

    try { 
        cv_ptr_ = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::MONO8);
    }
    catch (cv_bridge::Exception& e) {
        RCLCPP_ERROR(this->get_logger(),"cv_bridge exception: %s", e.what());
    }

    frame_ = cv_ptr_->image; 
    frame_id_ = msg->header.frame_id;
    assert(frame_.empty()!=true); //does not work it seems
    
    if (count_ < num_ && (!frame_.empty())) {
        compression_params_.push_back(CV_IMWRITE_PNG_COMPRESSION);
        compression_params_.push_back(9);
        image_name_ =  std::to_string(count_++) + "-" + frame_id_  + ".png";

        cv::imwrite(image_name_, frame_, compression_params_); //TODO : Make this always point to etc folder
    }

}

}// namespace ariitk::ros2_bridge_test
