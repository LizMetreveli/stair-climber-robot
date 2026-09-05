#!/usr/bin/env python3

import cv2
import numpy as np
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_msgs.msg import String
from cv_bridge import CvBridge
from ultralytics import YOLO

class TrafficLightDetector(Node):
    def __init__(self):
        super().__init__('traffic_light_node')
        self.bridge = CvBridge()
        
        # Publisher for detected light status
        self.color_publisher = self.create_publisher(String, 'traffic_light_topic', 10)
        
        # Subscribe to camera feed instead of accessing hardware directly
        self.image_subscription = self.create_subscription(
            Image,
            '/camera/image_raw',
            self.image_callback,
            10
        )
        
        # Load YOLO model
        self.model = YOLO("yolov8n.pt")

    def image_callback(self, msg: Image):
        try:
            # Convert ROS Image message to OpenCV format
            frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        except Exception as e:
            self.get_logger().error(f'cv_bridge exception: {e}')
            return

        self.detect_traffic_light(frame)

    def detect_traffic_light(self, frame):
        # Run YOLO inference
        results = self.model(frame, classes=[9], imgsz=256, vid_stride=2, verbose=False)
        
        for result in results:
            if result.boxes:
                xywh = result.boxes.xywh.tolist()[0]
                
                # Convert ROI/HSV logic on the frame
                hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

                mask_red = cv2.inRange(hsv, np.array([0, 120, 70]), np.array([10, 255, 255]))
                mask_green = cv2.inRange(hsv, np.array([45, 100, 50]), np.array([75, 255, 255]))
                mask_yellow = cv2.inRange(hsv, np.array([20, 100, 100]), np.array([30, 255, 255]))

                red_pixels = cv2.countNonZero(mask_red)
                green_pixels = cv2.countNonZero(mask_green)
                yellow_pixels = cv2.countNonZero(mask_yellow)

                if red_pixels > green_pixels and red_pixels > yellow_pixels:
                    color = "09 red"
                elif green_pixels > red_pixels and green_pixels > yellow_pixels:
                    color = "09 Green"
                elif yellow_pixels > red_pixels and yellow_pixels > green_pixels:
                    color = "09 yellow"
                else:
                    color = "unknown"

                # Publish detected status
                msg = String()
                msg.data = color
                self.color_publisher.publish(msg)

        # Annotate and show frame window
        annotated_frames = results[0].plot()
        cv2.imshow('Traffic Light Monitor', annotated_frames)
        cv2.waitKey(1)

    def destroy_node(self):
        cv2.destroyAllWindows()
        super().destroy_node()


def main(args=None):
    rclpy.init(args=args)
    traffic_light_detector = TrafficLightDetector()
    try:
        rclpy.spin(traffic_light_detector)
    except KeyboardInterrupt:
        pass
    finally:
        traffic_light_detector.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
