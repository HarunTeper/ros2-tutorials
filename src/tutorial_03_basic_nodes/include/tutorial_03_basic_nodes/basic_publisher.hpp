#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/detail/header__struct.hpp>

class BasicPublisher : public rclcpp::Node
{
public:
  BasicPublisher();

private:
  void timer_callback();

  rclcpp::TimerBase::SharedPtr timer;
  rclcpp::Publisher<std_msgs::msg::Header>::SharedPtr publisher;
};