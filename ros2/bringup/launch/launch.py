from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()

    # 1. Physical Camera Publisher Node (Reads hardware /dev/video0)
    camera_pub_node = Node(
        package="camera",
        executable="camera_publisher",
        name="camera_publisher",
        output="screen"
    )

    # 2. QR Code Processing Node (Subscribes to image feed & flashes LED)
    qr_data_node = Node(
        package="camera",
        executable="qr_data",
        name="qr_data",
        output="screen"
    )

    # 3. QR Data Subscriber Node
    qr_sub_node = Node(
        package="camera",
        executable="qr_sub",
        name="qr_sub",
        output="screen"
    )

    # 4. Traffic Light Processing Node (Subscribes to image feed & runs YOLO)
    traffic_light_node = Node(
        package="camera",
        executable="traffic_light",
        name="traffic_light_node",
        output="screen"
    )

    # 5. Traffic Light Subscriber Node
    traffic_sub_node = Node(
        package="camera",
        executable="traffic_sub",
        name="traffic_sub",
        output="screen"
    )

    # 6. Keyboard Serial Node
    keyboard_serial_node = Node(
        package="keyboard_serial",
        executable="keyboard_serial",
        name="keyboard_serial",
        output="screen"
    )

    # Add all nodes to the Launch Description
    ld.add_action(camera_pub_node)
    ld.add_action(qr_data_node)
    ld.add_action(qr_sub_node)
    ld.add_action(traffic_light_node)
    ld.add_action(traffic_sub_node)
    ld.add_action(keyboard_serial_node)

    return ld
