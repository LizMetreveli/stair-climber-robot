# Chassis Design - Tracked Climbing Robot

Welcome to the mechanical design folder of our tracked robot project! This directory contains all the CAD files and 3D models necessary to build the chassis.

## Overview

This chassis was engineered in Fusion 360 to navigate challenging terrains and climb stairs up to a 33-degree incline. The core structure is designed to house a 4-motor all-wheel-drive (AWD) track system, ensuring adequate torque and stability, while managing the center of gravity.

### Key Design Features

*   **4-Motor Drive System:** Custom mounts (`DC motor holder`) for four JGA25-371 DC motors to evenly distribute the climbing load and prevent stall conditions.
*   **Camera Integration:** Forward-facing support engineered to securely hold the Logitech C270 HD Webcam for computer vision tasks.
*   **Intelligent Servo Brackets:** Integrated custom mounts for the Feetech STS3215 smart servos (including `STS3215_Side_bracket` and `STS3215_Main_bracket`).
*   **Electronics Bay:** A centralized mounting chassis (`big_base_25`) precisely modeled to fit the Raspberry Pi 4, Nucleo board, L298N motor drivers, buck converters, and the power supply system.
*   **Custom Drive System:** Specifically modeled hex-patterned drive wheels (`hex wheel`) and custom track mechanisms designed for maximum grip on stair edges.

## CAD Files Provided

*   **Native Models:** Original parametric workspace files to easily modify tolerances, brackets, or component placements.
*   **STEP Assembly:** A complete unified assembly file is provided for viewing the entire robot structure and checking clearances in your preferred CAD software.
*   **STL Export:** Individual parts exported and correctly oriented for direct manufacturing.

## License

This hardware design is released under the **CERN Open Hardware Licence (CERN-OHL)**. You are free to modify, distribute, and use these designs for both personal and commercial projects, provided you share your modifications under the same license.
