#include "tutorial_03_basic_nodes/basic_asynchronous_client.hpp"
#include <chrono>
#include <memory>
#include <std_srvs/srv/detail/set_bool__struct.hpp>

BasicAsynchronousClient::BasicAsynchronousClient() : Node("basic_asynchronous_client_node")
{
  timer = this->create_wall_timer(std::chrono::milliseconds(1000), [this]() { timer_callback(); });
  client = this->create_client<std_srvs::srv::SetBool>("basic_service");
}

void BasicAsynchronousClient::timer_callback()
{
  std_srvs::srv::SetBool::Request::SharedPtr request = std::make_shared<std_srvs::srv::SetBool::Request>();
  request->data = false;

  while (!client->wait_for_service(std::chrono::milliseconds(1000)))
  {
    if (!rclcpp::ok())
    {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  rclcpp::Client<std_srvs::srv::SetBool>::SharedFuture result =
      client->async_send_request(request, [this](const rclcpp::Client<std_srvs::srv::SetBool>::SharedFuture future) {
        BasicAsynchronousClient::service_callback(future);
      });
}

void BasicAsynchronousClient::service_callback(const rclcpp::Client<std_srvs::srv::SetBool>::SharedFuture future)
{
  std_srvs::srv::SetBool::Response::SharedPtr response = future.get();
  response.get();
  std::cout << "Received response. message " << response->message << "  "
            << " success " << response->success << std::endl;
}

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BasicAsynchronousClient>());
  rclcpp::shutdown();
  return 0;
}