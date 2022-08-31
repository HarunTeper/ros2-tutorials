#include <rclcpp/rclcpp.hpp>
#include <rclcpp/subscription.hpp>
#include <std_msgs/msg/detail/header__struct.hpp>

class BasicSubscription : public rclcpp::Node
{
public:
  BasicSubscription();

private:
  void subscription_callback(const std_msgs::msg::Header);
  rclcpp::Subscription<std_msgs::msg::Header>::SharedPtr subscription;
};