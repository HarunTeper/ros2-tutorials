#!/usr/bin/env python3
"""ROS2 Python shebang"""

from launch_ros.actions import Node
from launch import LaunchDescription

def generate_launch_description():
    """Returns launch description"""

    # Nodes
    service_node = Node(
        package='tutorial_03_basic_nodes',
        executable='basic_service',
        name='basic_service',
        output='screen'
    )

    client_node = Node(
        package='tutorial_03_basic_nodes',
        executable='basic_asynchronous_client',
        name='basic_asynchronous_client',
        output='screen'
    )

    # Launch Description
    launch_description = LaunchDescription()

    launch_description.add_action(service_node)
    launch_description.add_action(client_node)

    return launch_description
