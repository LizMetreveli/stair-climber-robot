#!/usr/bin/env python3

import cv2
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_msgs.msg import String
from cv_bridge import CvBridge
from gpiozero import LED

class QRCodeNode(Node):
    def __init__(self):
        super().__init__('qr_code_node')
        self.bridge = CvBridge()
        self.detector = cv2.QRCodeDetector()
        
        # Subscribes to raw camera frames
        self.img_sub = self.create_subscription(
            Image, 
            '/camera/image_raw', 
            self.image_callback, 
            10
        )
        
        # Publishes decoded string data
        self.qr_pub = self.create_publisher(String, 'qr_data', 10)
        
        # Initialize LED on BCM pin 22
        self.led = LED(22)
        self.last_data = None
        self.blinking = False

    def image_callback(self, msg: Image):
        try:
            # Convert ROS Image to OpenCV frame
            frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        except Exception as e:
            self.get_logger().error(f'cv_bridge exception: {e}')
            return

        # Detect and decode QR code
        try:
            data, bbox, _ = self.detector.detectAndDecode(frame)
        except cv2.error as e:
            # OpenCV's QRCodeDetector can throw a convexHull assertion error
            # on certain malformed/partial frames. Skip this frame instead of
            # crashing the node.
            self.get_logger().warn(f'QR detection failed on this frame, skipping: {e}')
            return

        if len(data) > 0:
            # Start continuous blinking as soon as a QR code is visible,
            # and keep it going for as long as one stays in view.
            if not self.blinking:
                self.start_blink()

            if data != self.last_data:
                self.get_logger().info(f"QR Detected: {data}")

                # Publish QR string
                qr_msg = String()
                qr_msg.data = data
                self.qr_pub.publish(qr_msg)

                self.last_data = data
        else:
            # No QR in view anymore: stop blinking and reset state.
            if self.blinking:
                self.stop_blink()
            self.last_data = None

        # Display window
        cv2.imshow('QR Code Feed', frame)
        cv2.waitKey(1)

    def start_blink(self):
        # n=None makes gpiozero blink indefinitely in the background until
        # stop_blink()/led.off() is called.
        self.led.blink(on_time=0.1, off_time=0.1, n=None, background=True)
        self.blinking = True

    def stop_blink(self):
        self.led.off()
        self.blinking = False

    def destroy_node(self):
        cv2.destroyAllWindows()
        self.led.off()
        self.led.close()
        super().destroy_node()

def main(args=None):
    rclpy.init(args=args)
    node = QRCodeNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
