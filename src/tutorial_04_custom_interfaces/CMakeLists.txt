cmake_minimum_required(VERSION 3.5)
project(tutorial_04_custom_interfaces)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(tutorial_interfaces REQUIRED)

# Include Cpp "include" directory
include_directories(include)

# Create Cpp executable
add_executable(basic_publisher src/basic_publisher.cpp)
ament_target_dependencies(basic_publisher rclcpp std_msgs tutorial_interfaces)

add_executable(basic_subscription src/basic_subscription.cpp)
ament_target_dependencies(basic_subscription rclcpp std_msgs tutorial_interfaces)

add_executable(basic_service src/basic_service.cpp)
ament_target_dependencies(basic_service rclcpp std_srvs tutorial_interfaces)

add_executable(basic_asynchronous_client src/basic_asynchronous_client.cpp)
ament_target_dependencies(basic_asynchronous_client rclcpp std_srvs tutorial_interfaces)

# Install Cpp executables
install(TARGETS
  basic_publisher
  basic_subscription
  basic_service
  basic_asynchronous_client
  DESTINATION lib/${PROJECT_NAME}
)

# Install Python modules
ament_python_install_package(${PROJECT_NAME})

# Install Python executables
install(PROGRAMS
  scripts/py_node.py
  DESTINATION lib/${PROJECT_NAME}
)
ament_package()
