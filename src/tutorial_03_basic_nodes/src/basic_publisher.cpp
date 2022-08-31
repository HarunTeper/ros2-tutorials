#include "tutorial_03_basic_nodes/basic_publisher.hpp"

BasicPublisher::BasicPublisher() : rclcpp::Node("basic_publisher_node")
{
  timer = this->create_wall_timer(std::chrono::milliseconds(1000), [this]() { timer_callback(); });
  publisher = this->create_publisher<std_msgs::msg::Header>("basic_topic", 1);
}

void BasicPublisher::timer_callback()
{
  std_msgs::msg::Header msg;
  msg.stamp = this->get_clock()->now();
  msg.frame_id = "basic_publisher_frame";
  publisher->publish(msg);
  std::cout << "Sent message: frame_id \"" << msg.frame_id << "\" stamp \"" << msg.stamp.sec << " " << msg.stamp.nanosec << "\"" << std::endl;
}

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BasicPublisher>());
  rclcpp::shutdown();
  return 0;
}