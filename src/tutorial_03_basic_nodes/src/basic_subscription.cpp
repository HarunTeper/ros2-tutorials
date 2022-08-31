#include "tutorial_03_basic_nodes/basic_subscription.hpp"

BasicSubscription::BasicSubscription() : Node("basic_subscription_node")
{
  subscription = this->create_subscription<std_msgs::msg::Header>(
      "basic_topic", 1, [this](std_msgs::msg::Header msg) { subscription_callback(msg); });
}

void BasicSubscription::subscription_callback(const std_msgs::msg::Header msg)
{
  std::cout << "Received message: frame_id \"" << msg.frame_id << "\" stamp \"" << msg.stamp.sec << " " << msg.stamp.nanosec << "\"" << std::endl;
}

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BasicSubscription>());
  rclcpp::shutdown();
  return 0;
}