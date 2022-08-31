#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/detail/set_bool__struct.hpp>
#include <std_srvs/srv/set_bool.hpp>

class BasicAsynchronousClient : public rclcpp::Node
{
public:
  BasicAsynchronousClient();

private:
  void timer_callback();
  void service_callback(const rclcpp::Client<std_srvs::srv::SetBool>::SharedFuture future);

  rclcpp::Client<std_srvs::srv::SetBool>::SharedPtr client;
  rclcpp::TimerBase::SharedPtr timer;
};