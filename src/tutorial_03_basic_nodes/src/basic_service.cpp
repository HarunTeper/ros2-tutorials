#include "tutorial_03_basic_nodes/basic_service.hpp"

BasicService::BasicService() : Node("basic_service_node")
{
  service = this->create_service<std_srvs::srv::SetBool>(
      "basic_service", [this](const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
                              std::shared_ptr<std_srvs::srv::SetBool::Response> response) {
        BasicService::service_callback(request, response);
      });
}

void BasicService::service_callback(const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
                                    std::shared_ptr<std_srvs::srv::SetBool::Response> response)
{
  response->success = !request->data;
  response->message = "Response = !Request";
  std::cout << "Received request " << request->data << " Set response " << response->success << std::endl;
}

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BasicService>());
  rclcpp::shutdown();
  return 0;
}