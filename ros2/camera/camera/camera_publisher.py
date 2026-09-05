#!/usr/bin/env python3

import cv2
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge

class CameraPublisher(Node):
    def __init__(self):
        super().__init__('camera_publisher')

        self.publisher = self.create_publisher(Image, '/camera/image_raw', 1)
        self.bridge = CvBridge()

        self.cap = cv2.VideoCapture(0)

        if not self.cap.isOpened():
            self.get_logger().error("Could not open camera!")
        else:
            self.get_logger().info("Camera opened.")

    def run(self):
        while rclpy.ok():
            ret, frame = self.cap.read()

            if ret:
                msg = self.bridge.cv2_to_imgmsg(frame, encoding='bgr8')
                self.publisher.publish(msg)
            else:
                self.get_logger().warn("Failed to capture frame")

            # Process ROS callbacks
            rclpy.spin_once(self, timeout_sec=0)

        self.cap.release()

def main(args=None):
    rclpy.init(args=args)

    node = CameraPublisher()

    try:
        node.run()
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
