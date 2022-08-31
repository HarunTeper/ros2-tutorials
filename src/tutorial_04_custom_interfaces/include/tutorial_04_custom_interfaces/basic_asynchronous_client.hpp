#include <rclcpp/rclcpp.hpp>
#include <tutorial_interfaces/srv/hello_world.hpp>

class BasicAsynchronousClient : public rclcpp::Node
{
public:
  BasicAsynchronousClient();

private:
  void timer_callback();
  void service_callback(const rclcpp::Client<tutorial_interfaces::srv::HelloWorld>::SharedFuture future);

  rclcpp::Client<tutorial_interfaces::srv::HelloWorld>::SharedPtr client;
  rclcpp::TimerBase::SharedPtr timer;
};