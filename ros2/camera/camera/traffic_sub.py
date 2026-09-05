#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class TrafficSubscriber(Node):
    def __init__(self):
        super().__init__("traffic_subscriber_node")
        self.traffic_sub = self.create_subscription(
            String,
            '/traffic_light_topic',
            self.traffic_callback,
            10
        )

    def traffic_callback(self, msg: String):
        self.get_logger().info(f"Traffic Light State: {msg.data}")

def main(args=None):
    rclpy.init(args=args)
    node = TrafficSubscriber()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
