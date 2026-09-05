# ROS2 Control & Vision

ROS2-based high-level control and computer vision software for the tracked mobile robot developed for the **Advanced Robotics Challenge**.

The system runs on a **Raspberry Pi 4** and provides camera streaming, computer-vision processing, keyboard control, and serial communication with the STM32 low-level controller.

## Features

* ROS2-based modular software architecture
* Live camera publishing using OpenCV and `cv_bridge`
* QR code detection and decoding
* Traffic-light detection using YOLOv8 and OpenCV
* Keyboard-based robot control
* Serial communication between Raspberry Pi and STM32
* ROS2 launch package for starting the complete system

## ROS2 Packages

### `camera`

Handles camera acquisition and computer-vision functionality.

The camera publisher captures frames from the physical camera and publishes them to:

```text
/camera/image_raw
```

Other vision nodes subscribe to this shared camera stream rather than accessing the camera independently.

The package includes:

* **`camera_publisher`** — captures and publishes the camera feed
* **`qr_data`** — detects and decodes QR codes and publishes the decoded data
* **`qr_sub`** — subscribes to and displays received QR data
* **`traffic_light`** — detects traffic lights using YOLOv8 and classifies their state using OpenCV image processing
* **`traffic_sub`** — subscribes to the detected traffic-light state

### `keyboard_serial`

Provides manual control of the robot through keyboard input.

Valid keyboard commands are transmitted over serial from the Raspberry Pi to the **STM32 Nucleo-F091RC**, where they are interpreted by the robot's low-level control software.

Communication is configured at **115200 baud**.

### `bringup`

ROS2 launch package used to start the robot's high-level software components together, including:

* Camera publisher
* QR detection
* QR data subscriber
* Traffic-light detection
* Traffic-light subscriber
* Keyboard-to-serial control

## Computer Vision

### QR Code Detection

OpenCV's `QRCodeDetector` is used to detect and decode QR codes from the ROS2 camera stream.

When a QR code is detected, the decoded string is published as a ROS2 message. The prototype also uses a Raspberry Pi GPIO-connected LED to provide a visual indication while a QR code is visible.

### Traffic-Light Detection

Traffic-light detection combines **YOLOv8n** object detection with OpenCV image processing.

YOLO is used to identify traffic lights in the camera feed, while HSV-based image processing is used to determine the detected light state.

The resulting state is published through ROS2 for use by other nodes.

## Robot Control

The robot is manually controlled using keyboard commands.

The `keyboard_serial` node captures supported key inputs and transmits them from the Raspberry Pi to the STM32 over USB serial. The STM32 then performs the corresponding low-level drivetrain, chassis, or manipulator action.

This separates the system into:

**Raspberry Pi / ROS2** — high-level input, vision and communication

**STM32** — low-level hardware and actuator control

## Technologies

* ROS2
* Python
* Raspberry Pi 4
* OpenCV
* YOLOv8 / Ultralytics
* `cv_bridge`
* PySerial
* GPIO
* STM32

## Project Context

This software forms the high-level control and vision layer of the **ROS2 Stair-Climbing Mobile Robot** developed for the Advanced Robotics Challenge.

It operates alongside the STM32 low-level control software responsible for the robot's motors, chassis mechanism, and manipulator.
