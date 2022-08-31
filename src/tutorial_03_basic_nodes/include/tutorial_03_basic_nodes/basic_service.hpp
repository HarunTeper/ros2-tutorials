#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/set_bool.hpp>

class BasicService : public rclcpp::Node
{
public:
  BasicService();

private:
  void service_callback(const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
          std::shared_ptr<std_srvs::srv::SetBool::Response>      response);

  rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr service;
  rclcpp::TimerBase::SharedPtr timer;
};