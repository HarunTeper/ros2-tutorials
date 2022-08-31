#include "tutorial_03_basic_nodes/basic_synchronous_client.hpp"
#include <chrono>
#include <future>

BasicSynchronousClient::BasicSynchronousClient() : Node("basic_synchronous_client_node")
{
  timer = this->create_wall_timer(std::chrono::milliseconds(1000), [this]() { timer_callback(); });
  client = this->create_client<std_srvs::srv::SetBool>("basic_service");
}

void BasicSynchronousClient::timer_callback()
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
  rclcpp::Client<std_srvs::srv::SetBool>::SharedFuture future = client->async_send_request(request);


  std_srvs::srv::SetBool::Response::SharedPtr result = future.get();

  std::cout << "Received result. Message" << result->message <<" success " << result->success << std::endl;
}

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BasicSynchronousClient>());
  rclcpp::shutdown();
  return 0;
}