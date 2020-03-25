cmake_minimum_required(VERSION 3.5)
project(ros2_bridge_test)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(OpenCV REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)


include_directories(include)
ament_export_include_directories(include)

#target_include_directories(${PROJECT_NAME}_lib
 # PUBLIC
  #  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
   # $<INSTALL_INTERFACE:include>)

add_library(${PROJECT_NAME}_lib SHARED src/ros2_image_sub.cpp)
target_link_libraries(${PROJECT_NAME}_lib ${ament_LIBRARIES} ${OpenCV_LIBRARIES})

ament_target_dependencies(${PROJECT_NAME}_lib 
  "rclcpp" 
  "OpenCV" 
  "sensor_msgs"
  "cv_bridge"
)

add_executable(${PROJECT_NAME}_node src/${PROJECT_NAME}_node.cpp)
target_link_libraries(${PROJECT_NAME}_node ${ament_LIBRARIES} ${PROJECT_NAME}_lib)
ament_target_dependencies(${PROJECT_NAME}_node "rclcpp")

install(DIRECTORY include/${PROJECT_NAME}/
    DESTINATION include/${PROJECT_NAME}
    FILES_MATCHING PATTERN "*.hpp")

install(TARGETS ${PROJECT_NAME}_lib
        DESTINATION lib
)

install(TARGETS
  ${PROJECT_NAME}_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
