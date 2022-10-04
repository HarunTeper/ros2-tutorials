#include "tutorial_05_parameters/basic_subscription.hpp"

BasicSubscription::BasicSubscription() : Node("basic_subscription_node")
{
  subscription = this->create_subscription<tutorial_interfaces::msg::StringArray>(
      "basic_topic", 1, [this](tutorial_interfaces::msg::StringArray msg) { subscription_callback(msg); });
}

void BasicSubscription::subscription_callback(const tutorial_interfaces::msg::StringArray msg)
{
  std::cout << "Received message: frame_id \"" << msg.header.frame_id << "\" stamp \"" << msg.header.stamp.sec << " "
            << msg.header.stamp.nanosec << "\"" << std::endl;
  for (std::string elem : msg.strings)
  {
    std::cout << elem << std::endl;
  }
}

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BasicSubscription>());
  rclcpp::shutdown();
  return 0;
}