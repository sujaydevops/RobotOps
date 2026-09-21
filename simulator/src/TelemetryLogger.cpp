#include "TelemetryLogger.h"

#include <fstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>

TelemetryLogger::TelemetryLogger(const std::string& filename)
    : filename(filename) {}

void TelemetryLogger::initialize() {
    std::ofstream file(filename);

    file << "timestamp,robot_id,battery,temperature,speed,"
            "x_position,y_position,status,error_code\n";
}

void TelemetryLogger::log(const Robot& robot) {
    std::ofstream file(filename, std::ios::app);

    auto now = std::chrono::system_clock::now();
    std::time_t currentTime =
        std::chrono::system_clock::to_time_t(now);

    std::tm* timeInfo = std::localtime(&currentTime);

    std::ostringstream timestamp;
    timestamp << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S");

    file << timestamp.str() << ","
         << robot.getId() << ","
         << std::fixed << std::setprecision(2)
         << robot.getBattery() << ","
         << robot.getTemperature() << ","
         << robot.getSpeed() << ","
         << robot.getXPosition() << ","
         << robot.getYPosition() << ","
         << robot.getStatus() << ","
         << robot.getErrorCode()
         << "\n";
}

