#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/set_bool.hpp>

class BasicSynchronousClient : public rclcpp::Node
{
public:
  BasicSynchronousClient();

private:
  void timer_callback();

  rclcpp::Client<std_srvs::srv::SetBool>::SharedPtr client;
  rclcpp::TimerBase::SharedPtr timer;
};