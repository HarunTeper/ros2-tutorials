#!/usr/bin/env python3
"""ROS2 Python shebang"""

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
