# Tutorial 03 - Basic Nodes

In this tutorial, you will learn about the basic components of ROS2 systems and how they communicate.

## Node Creation

A node is a system component that includes functions to receive, process, and forward data.
In C++, nodes can be split up into the header file (.hpp) and the source file (.cpp).
The header file contains an overview of the defined method functions, while the source file includes the implementation of all defined functions.

The basic publisher header file contains the following code:

```text
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/detail/header__struct.hpp>

class BasicPublisher : public rclcpp::Node
{
public:
  BasicPublisher();

private:
  void timer_callback();

  rclcpp::TimerBase::SharedPtr timer;
  rclcpp::Publisher<std_msgs::msg::Header>::SharedPtr publisher;
};
```

Let's go over each part of the header file:

```text
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/detail/header__struct.hpp>
```

These commands include the functions that are provided by ROS2, such as nodes, topics, publishers, subscriptions, etc..
In addition, we include a message type that we use for communication.

```text
class BasicPublisher : public rclcpp::Node
```

We define a new node (rclcpp::Node) class with the name BasicPublisher.

```text
public:
  BasicPublisher();
```

We define the constructor as a basic function that can be called by launch files to start the node.

```text
private:
  void timer_callback();

  rclcpp::TimerBase::SharedPtr timer;
  rclcpp::Publisher<std_msgs::msg::Header>::SharedPtr publisher;
```

We define private variables of the node, such as variables, publishers, timers, subscriptions, etc..
In general, a node is a generic class that features ROS2 functionalities for communication with other nodes.

Now let's examine the its source file:

```text
#include "tutorial_03_basic_nodes/basic_publisher.hpp"

BasicPublisher::BasicPublisher() : rclcpp::Node("basic_publisher_node")
{
  timer = this->create_wall_timer(std::chrono::milliseconds(1000), [this]() { timer_callback(); });
  publisher = this->create_publisher<std_msgs::msg::Header>("basic_topic", 1);
}

void BasicPublisher::timer_callback()
{
  std_msgs::msg::Header msg;
  msg.stamp = this->get_clock()->now();
  msg.frame_id = "basic_publisher_frame";
  publisher->publish(msg);
  std::cout << "Sent message: frame_id \"" << msg.frame_id << "\" stamp \"" << msg.stamp.sec << " " << msg.stamp.nanosec << "\"" << std::endl;
}

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BasicPublisher>());
  rclcpp::shutdown();
  return 0;
}
```

Let's go over each part of the source file:

```text
#include "tutorial_03_basic_nodes/basic_publisher.hpp"
```

We include the header file, which should in turn include all functions that are required for the source file.

```text
BasicPublisher::BasicPublisher() : rclcpp::Node("basic_publisher_node")
{
  timer = this->create_wall_timer(std::chrono::milliseconds(1000), [this]() { timer_callback(); });
  publisher = this->create_publisher<std_msgs::msg::Header>("basic_topic", 1);
}
```

We implement the constructor, and create a node with the name "basic_publisher_node".
In addition, we create a timer with a period and a callback.
The period is the rate at which the timer callback function will be called.
The callback "timer_callback" is a node function that is called every time the timer is executed.
In addition, we create a publisher with a destination topic "basic_topic" and a buffer size of one.

```text
void BasicPublisher::timer_callback()
{
  std_msgs::msg::Header msg;
  msg.stamp = this->get_clock()->now();
  msg.frame_id = "basic_publisher_frame";
  publisher->publish(msg);
  std::cout << "Sent message: frame_id \"" << msg.frame_id << "\" stamp \"" << msg.stamp.sec << " " << msg.stamp.nanosec << "\"" << std::endl;
}
```

We create the callback for the timer, which creates a message "msg", sets the message contents for "stamp" and "frame_id", and uses the publisher to send the message to the topic "basic_topic".

```text
int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BasicPublisher>());
  rclcpp::shutdown();
  return 0;
}
```

We create a main function, which creates the node when called and executes it using the rclcpp::spin function.
When the node is turned off, rclcpp will be shutdown correctly and the main function returns.

## Node Execution

You can run a node using the following template

```text
ros2 run <package_name> <node_name> <args>
```

The package name for this package would be "tutorial_03_basic_nodes", while the node_name would be "basic_publisher" to start the previously described node.
The "args" argument provides arguments, which can be used by the main function (via argc and argv) to pass the argument to the node constructor for example.

## Launch Files

Nodes can also be launched via launch files, which can simultaneously start multiple nodes from the current package. In addition, launch files can be used to run nodes and launch files from other packages as well.

Launch files can be written in Python and XML.
For basic nodes that do not require custom parameters, XML files provide enough functionalitiy to launch basic setups.

Let's look at the launch_publisher_subscription.launch.xml file:

```text
<launch>
    <node pkg="tutorial_03_basic_nodes" exec="basic_subscription"   
    name="basic_subscription" output="screen"/>
    <node pkg="tutorial_03_basic_nodes" exec="basic_publisher" 
    name="basic_publisher" output="screen"/>
</launch>
```

For each node, we define a node block that specifies the package, executable name, and node name.
The executable name is specified in the CMakeLists.txt file for each source file.

Now let's take a look at the launch_publisher_subscription.launch.py file.

```text
"""Launch file name"""

from launch_ros.actions import Node
from launch import LaunchDescription

def generate_launch_description():
    """Returns launch description"""

    # Nodes
    publisher_node = Node(
        package='tutorial_03_basic_nodes',
        executable='basic_publisher',
        name='basic_publisher',
        output='screen'
    )

    subscriber_node = Node(
        package='tutorial_03_basic_nodes',
        executable='basic_subscription',
        name='basic_subscription',
        output='screen'
    )

    # Launch Description
    launch_description = LaunchDescription()

    launch_description.add_action(publisher_node)
    launch_description.add_action(subscriber_node)

    return launch_description
```

Let's go over each part:

```text
from launch_ros.actions import Node
from launch import LaunchDescription
```

First, we import the required ROS2 functions for the launch files.

```text
def generate_launch_description():
```

We create a "generate_launch_description" function, that specifies the launch description, including nodes, launch files, and arguments that we want to start.

```text
# Nodes
    publisher_node = Node(
        package='tutorial_03_basic_nodes',
        executable='basic_publisher',
        name='basic_publisher',
        output='screen'
    )

    subscriber_node = Node(
        package='tutorial_03_basic_nodes',
        executable='basic_subscription',
        name='basic_subscription',
        output='screen'
    )
```

Then, we create the nodes that should be launched. We specify the packages, executables and node names.

```text
    # Launch Description
    launch_description = LaunchDescription()

    launch_description.add_action(publisher_node)
    launch_description.add_action(subscriber_node)

    return launch_description
```

Finally, we create the launch descriptions and add all arguments, nodes, and launch files that are required to launch the system.

The launch files can be run from the workspace directory using the following command:

```text
ros2 launch <package_name> <launch_file_name> <arguments>
```

For the previously described launch file, the package name is "tutorial_03_basic_nodes", the launch file name is "launch_publisher_subscriber.launch.py" and there are no additional arguments.

## Node Inspection

After launching the nodes, you can observe the runtime behavior of the nodes and the topics using commands that are provided by ROS2.

First, you can list all nodes that are currently running using the following command:

```text
ros2 node list
```

For specific nodes, you can get more details using the following commands:

```text
ros2 node info <node_name>
```

The same commands can be applied to topics:

```text
ros2 topic list
ros2 topic info <topic>
```

In addition, you can echo the topic contents using the following command:

```text
ros2 topic echo <topic>
```

Furthermore, you can use the following command to create a system graph:

```text
ros2 run rqt_graph rqt_graph
```
