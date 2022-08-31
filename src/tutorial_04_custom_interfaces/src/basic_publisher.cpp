#include "tutorial_04_custom_interfaces/basic_publisher.hpp"

BasicPublisher::BasicPublisher() : rclcpp::Node("basic_publisher_node")
{
  timer = this->create_wall_timer(std::chrono::milliseconds(1000), [this]() { timer_callback(); });
  publisher = this->create_publisher<tutorial_interfaces::msg::StringArray>("basic_topic", 1);
}

void BasicPublisher::timer_callback()
{
  tutorial_interfaces::msg::StringArray msg;
  msg.header.stamp = this->get_clock()->now();
  msg.header.frame_id = "basic_publisher_frame";
  msg.strings.push_back("TestString");
  publisher->publish(msg);
  std::cout << "Sent message: frame_id \"" << msg.header.frame_id << "\" stamp \"" << msg.header.stamp.sec << " " << msg.header.stamp.nanosec << "\"" << std::endl;
}

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BasicPublisher>());
  rclcpp::shutdown();
  return 0;
}