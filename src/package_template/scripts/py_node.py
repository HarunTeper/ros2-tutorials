#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

class PyNodeTemplate(Node):

    def __init__(self):
        super().__init__('py_node_template')
        print("Py node created")

def main(args=None):
    rclpy.init(args=args)

    py_node_template = PyNodeTemplate()

    rclpy.spin(py_node_template)

    py_node_template.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()