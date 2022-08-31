#!/usr/bin/env python3
import rclpy
from rclpy.node import Node


class PyNodeTemplate(Node):
    """Create a python node"""

    def __init__(self):
        super().__init__('py_node_template')
        print("Py node created")


def main(args=None):
    """Main function to create and spin a python node"""
    rclpy.init(args=args)

    py_node_template = PyNodeTemplate()

    rclpy.spin(py_node_template)

    py_node_template.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
