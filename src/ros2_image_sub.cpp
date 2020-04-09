#include <ros2_bridge_test/ros2_bridge_test.hpp>

using std::placeholders::_1;

namespace ariitk::ros2_bridge_test {

ImageSubscriber::ImageSubscriber(): Node("image_subscriber") {
      subscription_ = this->create_subscription<sensor_msgs::msg::Image>("bridge_image", 10, std::bind(&ImageSubscriber::imageCallback, this, _1));
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
    
    assert(frame_.empty()!=true); //does not work it seems
    if (!frame_.empty()) {
        
        auto time_point =std::chrono::system_clock::now(); 
        std::time_t now_c = std::chrono::system_clock::to_time_t(time_point);
        time_stamp_ = msg->header.stamp.sec;
        std::cout <<  "Time from stamp "<< time_stamp_<< " Time in system: "<< now_c <<  std::endl;
    
    }
    
}

}// namespace ariitk::ros2_bridge_test
