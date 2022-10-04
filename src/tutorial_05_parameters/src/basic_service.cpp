#include "tutorial_05_parameters/basic_service.hpp"

BasicService::BasicService() : Node("basic_service_node")
{
  service = this->create_service<tutorial_interfaces::srv::HelloWorld>(
      "basic_service", [this](const std::shared_ptr<tutorial_interfaces::srv::HelloWorld::Request> request,
                              std::shared_ptr<tutorial_interfaces::srv::HelloWorld::Response> response) {
        BasicService::service_callback(request, response);
      });
}

void BasicService::service_callback(const std::shared_ptr<tutorial_interfaces::srv::HelloWorld::Request> request,
                                    std::shared_ptr<tutorial_interfaces::srv::HelloWorld::Response> response)
{
  response->response = "Hello "+request->name;
  std::cout << "Received request from " << request->name << " Set response " << response->response << std::endl;
}

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BasicService>());
  rclcpp::shutdown();
  return 0;
}