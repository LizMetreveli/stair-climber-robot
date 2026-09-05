#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class QrDataSubscriber(Node):
    def __init__(self):
        super().__init__('qr_subscriber_node')
        self.qr_sub = self.create_subscription(
            String,
            '/qr_data',
            self.qr_callback,
            10
        )

    def qr_callback(self, msg: String):
        self.get_logger().info(f"Received QR Data: {msg.data}")

def main(args=None):
    rclpy.init(args=args)
    node = QrDataSubscriber()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
