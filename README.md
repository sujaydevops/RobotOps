# 🤖 RobotOps

A Linux-based robotics monitoring and telemetry simulation system built with modern C++.

RobotOps simulates multiple robots, generates changing telemetry data, evaluates robot health, and displays operational status in real time. The project is designed to demonstrate practical C++ development, Linux workflows, object-oriented programming, telemetry handling, and Git-based software engineering.

## Overview

Robotics systems depend on continuous monitoring of operational data such as battery level, temperature, movement speed, and system health.

RobotOps provides a lightweight simulation of that workflow.

The application manages multiple simulated robots and continuously updates their telemetry while evaluating their current operating status.

## Features

- Multi-robot telemetry simulation
- Real-time battery monitoring
- Temperature monitoring
- Robot speed tracking
- Position tracking
- Automated health evaluation
- Operational status reporting
- Error-code support
- Structured telemetry logging
- Continuous monitoring loop
- Modular C++ architecture

## Example Output

```text
RBT-001 | ONLINE | Battery: 98.51% | Temp: 38.08 C | Speed: 1.11 m/s
RBT-002 | ONLINE | Battery: 98.96% | Temp: 36.70 C | Speed: 1.13 m/s
RBT-003 | ONLINE | Battery: 98.56% | Temp: 36.50 C | Speed: 1.99 m/s
RBT-004 | ONLINE | Battery: 98.65% | Temp: 34.85 C | Speed: 0.35 m/s
RBT-005 | ONLINE | Battery: 98.56% | Temp: 35.56 C | Speed: 1.86 m/s
```

## Architecture

RobotOps separates robot behavior, telemetry logging, and application control into individual components.

```text
RobotOps
│
├── Robot
│   ├── telemetry state
│   ├── simulated updates
│   └── health evaluation
│
├── TelemetryLogger
│   └── telemetry recording
│
└── Main Application
    ├── manages robot fleet
    ├── updates telemetry
    └── displays system status
```

This structure keeps the project modular and makes it easier to extend with additional robotics functionality.

## Project Structure

```text
RobotOps/
├── simulator/
│   ├── include/
│   │   ├── Robot.h
│   │   └── TelemetryLogger.h
│   │
│   └── src/
│       ├── Robot.cpp
│       ├── TelemetryLogger.cpp
│       └── main.cpp
│
├── .gitignore
└── README.md
```

## Technologies

- C++17
- Linux
- GNU g++
- Git
- GitHub
- SSH
- Object-Oriented Programming

## Build

Clone the repository:

```bash
git clone git@github.com:sujaydevops/RobotOps.git
cd RobotOps
```

Compile:

```bash
g++ -std=c++17 -I simulator/include \
simulator/src/main.cpp \
simulator/src/Robot.cpp \
simulator/src/TelemetryLogger.cpp \
-o simulator/robotops
```

## Run

```bash
./simulator/robotops
```

Use:

```text
Ctrl + C
```

to stop the simulation.

## Core Components

### Robot

The `Robot` class represents an individual simulated robot and maintains information including:

- Robot ID
- Battery level
- Temperature
- Speed
- X/Y position
- Operational status
- Error code

Each robot updates its simulated telemetry and evaluates its operating condition.

### TelemetryLogger

The telemetry logger separates telemetry recording from robot behavior, providing a cleaner application architecture.

### Main Application

The main application creates and manages the robot fleet, updates each robot, evaluates system health, logs telemetry, and displays current operating information.

## Engineering Concepts Demonstrated

This project demonstrates practical use of:

- C++ classes and encapsulation
- Header/source file separation
- Object-oriented design
- Collections of objects
- Randomized simulation
- File I/O
- Continuous program execution
- Modular software architecture
- Linux command-line development
- Git version control
- SSH-based GitHub workflow

## Future Improvements

Planned extensions include:

- Automated unit testing
- Persistent telemetry storage
- Historical telemetry analysis
- Configurable alert thresholds
- Additional simulated robot sensors
- Backend API integration
- Web-based monitoring dashboard

## Author

**Sujay Gupta**

Computer Science Student  
City College of San Francisco

GitHub: `@sujaydevops`
