# RobotOps

A Linux-based robotics testing and telemetry platform built as a computer science portfolio project.

## Overview

RobotOps simulates robotic operations and generates telemetry data such as battery level, temperature, speed, position, and operational status.

The project is being developed incrementally to explore systems programming, backend development, Linux, databases, testing, and DevOps practices.

## Current Version — v0.1

The first version includes a C++ robot simulator capable of:

- Generating simulated robot telemetry
- Tracking battery consumption
- Simulating temperature changes
- Generating robot movement and speed
- Tracking X/Y position
- Detecting warning and critical temperature conditions
- Running continuously at timed intervals

## Technologies

- C++
- Linux
- Git

Planned technologies:

- Java
- Spring Boot
- PostgreSQL
- REST APIs
- Docker
- GitHub Actions
- Cloud deployment

## Architecture

Current architecture:

C++ Robot Simulator
        |
        v
Robot Telemetry

Future architecture:

C++ Robot Simulator
        |
        v
Java REST API
        |
        v
PostgreSQL
        |
        v
Web Dashboard

## Build and Run

Compile:

    g++ simulator/robot_simulator.cpp -o simulator/robot_simulator

Run:

    ./simulator/robot_simulator

Stop the simulator with Ctrl+C.

## Roadmap

- [x] Build initial C++ robot simulator
- [x] Generate basic telemetry
- [ ] Add structured telemetry logging
- [ ] Support multiple robots
- [ ] Build Java backend
- [ ] Create REST API
- [ ] Integrate PostgreSQL
- [ ] Build operations dashboard
- [ ] Add automated tests
- [ ] Containerize with Docker
- [ ] Add CI/CD
- [ ] Deploy application

## Purpose

RobotOps is a student engineering project focused on learning how multiple software components can work together to create a larger system.

The project will evolve as I continue studying C++, Java, Linux, software engineering, and backend development.
