# Generic EKF with Sensor Framework

A lightweight implementation of an **Extended Kalman Filter (EKF)** for robotic state estimation, coupled with a hardware-agnostic sensor framework. Designed to compute a robot's state using inertial measurements, with simplified calibration and built-in sensor error compensation.

---

## Overview
This project aims to:
1. Estimate a robot's state (position, velocity, and orientation) using **inertial measurements only**.
2. Abstract hardware-specific sensor details via a modular framework.
3. Enable calibration without complex procedures.
4. Automatically compensate for sensor biases and errors.

---

## Design Plan

┌───────────────────────┐       ┌───────────────────────┐
│                       │       │                       │
│    SensorManager      │<>─────│       Sensor          │<|──────┐
│                       │       │                       │        │
├───────────────────────┤       ├───────────────────────┤        │
│ + register_sensor(s)  │       │ + read()              │        │
│ + get_sensor_data()   │       │ + calibrate()         │        │
│ + auto_detect()       │       └───────────────────────┘        │
└───────────────────────┘                                        │
           ▲                                                     │
           │                                     ┌───────────────┴───────────────┐
           ▼                                     │                               │
┌───────────────────────┐        ┌─────────────────────────┐    ┌─────────────────────────┐
│                       │        │                         │    │                         │
│   RobotStateMachine   │        │   ExtendedKalmanFilter  │    │      RobotSimulator     │
│                       │        │                         │    │                         │
├───────────────────────┤        ├─────────────────────────┤    ├─────────────────────────┤
│ + transition(state)   │        │ + predict(u: controls)  │    │ + simulate_motion()     │
│ + get_current_state() │        │ + update(z: measurement)│    │ + inject_sensor_error() │
└───────────────────────┘        └─────────────────────────┘    └─────────────────────────┘
           ▲                              ▲  ▲                             ▲
           │                              │  │                             │
           │                              │  └──────────────┐              │
           │                   ┌──────────┴──────────┐      │              │
           │                   │                     │      │              │
           └───────────────────┤   RobotSystem (Main)├──────┘              │
                               │                     │                     │
                               ├─────────────────────│                     │
                               │ + run()             │<────────────────────┘
                               │ + handle_errors()   │
                               └─────────────────────┘

---

## Features
- **EKF Implementation**: Robust state prediction and update steps for nonlinear systems.
- **Sensor Abstraction**: Unified interface for IMUs, gyroscopes, accelerometers, etc.
- **Auto-Calibration**: Zero-motion detection and bias estimation during initialization.
- **Error Compensation**: Dynamic adjustment for sensor drift and noise.
- **Inertial Navigation Support**: Fuses angular rates and accelerations for pose estimation.

---

## References
- https://en.wikipedia.org/wiki/Rotation_matrix
- https://en.wikipedia.org/wiki/Extended_Kalman_filter
- https://en.wikipedia.org/wiki/Kalman_filter
- https://en.wikipedia.org/wiki/Inertial_navigation_system
- https://motion.cs.illinois.edu/RoboticSystems/CoordinateTransformations.html
- https://automaticaddison.com/extended-kalman-filter-ekf-with-python-code-example/
