#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "package_template/cpp_node.hpp"

CppNodeTemplate::CppNodeTemplate() : Node("node_template")
{
  std::cout << "Cpp node template created" << std::endl;
}

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CppNodeTemplate>());
  rclcpp::shutdown();
  return 0;
}