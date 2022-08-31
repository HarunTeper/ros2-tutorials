#include <rclcpp/rclcpp.hpp>
#include <tutorial_interfaces/msg/string_array.hpp>

class BasicSubscription : public rclcpp::Node
{
public:
  BasicSubscription();

private:
  void subscription_callback(const tutorial_interfaces::msg::StringArray);
  rclcpp::Subscription<tutorial_interfaces::msg::StringArray>::SharedPtr subscription;
};