import rclpy
from rclpy.node import Node
import serial
import sys
import select
import tty
import termios

KEYS = [
    'q', 'w', 'a', 's', 'd',
    'x', 'r', 'f', 'e', 'y',
    'h', 'u', 'j', 'i', 'k',
    'n', 'o', 'l', 'p', '1', 
    '2', '3', '4', '5', '6', 
    '7', '8', '9', '0'
]

def isData():
    return select.select([sys.stdin], [], [], 0)[0]

class KeyboardSerial(Node):
    def __init__(self):
        super().__init__('keyboard_serial')
        self.ser = serial.Serial(
            '/dev/ttyACM0',
            115200,
            timeout=0.1
        )
        self.get_logger().info("Connected to STM32")

    def send_key(self, key):
        self.ser.write((key + "\n").encode())
        self.get_logger().info(f"Sent: {key}")

def main(args=None):
    rclpy.init(args=args)
    node = KeyboardSerial()
    old_settings = termios.tcgetattr(sys.stdin)

    try:
        tty.setcbreak(sys.stdin.fileno())
        while rclpy.ok():
            if isData():
                key = sys.stdin.read(1)
                if key in KEYS:
                    node.send_key(key)
            
            # Adding timeout_sec keeps the CPU load low during spinning
            rclpy.spin_once(node, timeout_sec=0.01)

    except KeyboardInterrupt:
        pass

    finally:
        # Restore terminal settings and close resources 
        termios.tcsetattr(
            sys.stdin,
            termios.TCSADRAIN,
            old_settings
        )
        node.ser.close()
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
