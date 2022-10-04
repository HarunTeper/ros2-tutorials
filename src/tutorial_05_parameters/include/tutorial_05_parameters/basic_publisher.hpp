#include <rclcpp/rclcpp.hpp>
#include <tutorial_interfaces/msg/string_array.hpp>

class BasicPublisher : public rclcpp::Node
{
public:
  BasicPublisher();

private:
  void timer_callback();

  rclcpp::TimerBase::SharedPtr timer;
  rclcpp::Publisher<tutorial_interfaces::msg::StringArray>::SharedPtr publisher;

  std::string message;
};