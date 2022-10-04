#include <rclcpp/rclcpp.hpp>
#include <tutorial_interfaces/srv/hello_world.hpp>

class BasicService : public rclcpp::Node
{
public:
  BasicService();

private:
  void service_callback(const std::shared_ptr<tutorial_interfaces::srv::HelloWorld::Request> request,
          std::shared_ptr<tutorial_interfaces::srv::HelloWorld::Response>      response);

  rclcpp::Service<tutorial_interfaces::srv::HelloWorld>::SharedPtr service;
  rclcpp::TimerBase::SharedPtr timer;
};