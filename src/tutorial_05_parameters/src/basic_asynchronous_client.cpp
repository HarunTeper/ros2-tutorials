#include "tutorial_05_parameters/basic_asynchronous_client.hpp"

BasicAsynchronousClient::BasicAsynchronousClient() : Node("basic_asynchronous_client_node")
{
  timer = this->create_wall_timer(std::chrono::milliseconds(1000), [this]() { timer_callback(); });
  client = this->create_client<tutorial_interfaces::srv::HelloWorld>("basic_service");
}

void BasicAsynchronousClient::timer_callback()
{
  tutorial_interfaces::srv::HelloWorld::Request::SharedPtr request = std::make_shared<tutorial_interfaces::srv::HelloWorld::Request>();
  request->name = "World";

  while (!client->wait_for_service(std::chrono::milliseconds(1000)))
  {
    if (!rclcpp::ok())
    {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  rclcpp::Client<tutorial_interfaces::srv::HelloWorld>::SharedFuture result =
      client->async_send_request(request, [this](const rclcpp::Client<tutorial_interfaces::srv::HelloWorld>::SharedFuture future) {
        BasicAsynchronousClient::service_callback(future);
      });
}

void BasicAsynchronousClient::service_callback(const rclcpp::Client<tutorial_interfaces::srv::HelloWorld>::SharedFuture future)
{
  tutorial_interfaces::srv::HelloWorld::Response::SharedPtr response = future.get();
  response.get();
  std::cout << "Received response. message " << response->response << std::endl;
}

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BasicAsynchronousClient>());
  rclcpp::shutdown();
  return 0;
}