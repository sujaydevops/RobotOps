#include "Robot.h"
#include <random>

Robot::Robot(const std::string& robotId)
    : id(robotId),
      battery(100.0),
      temperature(35.0),
      speed(0.0),
      xPosition(0.0),
      yPosition(0.0),
      status("ONLINE"),
      errorCode("NONE") {}

void Robot::update() {
    static std::random_device rd;
    static std::mt19937 generator(rd());

    std::uniform_real_distribution<double> tempChange(-1.0, 1.5);
    std::uniform_real_distribution<double> speedChange(0.0, 3.0);
    std::uniform_real_distribution<double> movement(-1.5, 1.5);
    std::uniform_real_distribution<double> batteryDrain(0.1, 0.8);

    battery -= batteryDrain(generator);

    if (battery < 0.0)
        battery = 0.0;

    temperature += tempChange(generator);
    speed = speedChange(generator);
    xPosition += movement(generator);
    yPosition += movement(generator);

    evaluateHealth();
}

void Robot::evaluateHealth() {
    errorCode = "NONE";

    if (battery <= 10.0 || temperature >= 60.0) {
        status = "CRITICAL";

        if (battery <= 10.0)
            errorCode = "LOW_BATTERY";
        else
            errorCode = "OVERHEAT";
    }
    else if (battery <= 25.0 || temperature >= 50.0) {
        status = "WARNING";

        if (battery <= 25.0)
            errorCode = "BATTERY_WARNING";
        else
            errorCode = "TEMP_WARNING";
    }
    else {
        status = "ONLINE";
    }
}

std::string Robot::getId() const { return id; }
double Robot::getBattery() const { return battery; }
double Robot::getTemperature() const { return temperature; }
double Robot::getSpeed() const { return speed; }
double Robot::getXPosition() const { return xPosition; }
double Robot::getYPosition() const { return yPosition; }
std::string Robot::getStatus() const { return status; }
std::string Robot::getErrorCode() const { return errorCode; }
