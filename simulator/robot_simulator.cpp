#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <thread>
#include <chrono>
#include <ctime>
#include <sstream>
#include <string>

// Stores one robot's current telemetry
struct RobotTelemetry {
    int robotId;
    double battery;
    double temperature;
    double speed;
    double xPosition;
    double yPosition;
};

// Returns the current local time as a readable timestamp
std::string getTimestamp() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    std::ostringstream timestamp;
    timestamp << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");

    return timestamp.str();
}

// Converts robot ID 1 into RBT-001
std::string getRobotName(int robotId) {
    std::ostringstream name;

    name << "RBT-"
         << std::setw(3)
         << std::setfill('0')
         << robotId;

    return name.str();
}

int main() {

    // Starting robot state
    RobotTelemetry robot{
        1,      // Robot ID
        100.0,  // Battery %
        35.0,   // Temperature C
        0.0,    // Speed m/s
        0.0,    // X position
        0.0     // Y position
    };

    // Random number generator for simulated sensor data
    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_real_distribution<double> temperatureChange(-0.5, 0.8);
    std::uniform_real_distribution<double> speedChange(0.0, 2.5);
    std::uniform_real_distribution<double> movement(-1.0, 1.0);

    // Create the telemetry log file
    std::ofstream logFile("telemetry.csv");

    if (!logFile.is_open()) {
        std::cerr << "ERROR: Unable to create telemetry.csv\n";
        return 1;
    }

    // Write CSV column names
    logFile
        << "timestamp,"
        << "robot_id,"
        << "battery,"
        << "temperature,"
        << "speed,"
        << "x_position,"
        << "y_position,"
        << "status,"
        << "error_code\n";

    std::cout << "=================================\n";
    std::cout << "       ROBOTOPS SIMULATOR\n";
    std::cout << "       Telemetry Logger v0.2\n";
    std::cout << "=================================\n\n";

    // Continue simulation until battery reaches zero
    while (robot.battery > 0) {

        // Generate new simulated telemetry
        robot.battery -= 0.5;
        robot.temperature += temperatureChange(generator);
        robot.speed = speedChange(generator);

        robot.xPosition += movement(generator);
        robot.yPosition += movement(generator);

        std::string status = "NORMAL";
        std::string errorCode = "NONE";

        // Temperature warning
        if (robot.temperature > 45.0) {
            status = "WARNING";
            errorCode = "TEMP_HIGH";
        }

        // Critical temperature
        if (robot.temperature > 50.0) {
            status = "CRITICAL";
            errorCode = "TEMP_CRITICAL";
        }

        // Low battery warning
        if (robot.battery < 20.0 && status == "NORMAL") {
            status = "WARNING";
            errorCode = "BATTERY_LOW";
        }

        std::string timestamp = getTimestamp();
        std::string robotName = getRobotName(robot.robotId);

        // Format decimal values
        std::cout << std::fixed << std::setprecision(2);

        // Display telemetry in Linux terminal
        std::cout << "[" << timestamp << "]\n";
        std::cout << "Robot:       " << robotName << "\n";
        std::cout << "Battery:     " << robot.battery << "%\n";
        std::cout << "Temperature: " << robot.temperature << " C\n";
        std::cout << "Speed:       " << robot.speed << " m/s\n";

        std::cout << "Position:    ("
                  << robot.xPosition
                  << ", "
                  << robot.yPosition
                  << ")\n";

        std::cout << "Status:      " << status << "\n";
        std::cout << "Error Code:  " << errorCode << "\n";

        std::cout << "---------------------------------\n";

        // Save telemetry to CSV
        logFile
            << timestamp << ","
            << robotName << ","
            << std::fixed << std::setprecision(2)
            << robot.battery << ","
            << robot.temperature << ","
            << robot.speed << ","
            << robot.xPosition << ","
            << robot.yPosition << ","
            << status << ","
            << errorCode << "\n";

        // Immediately write the latest record to disk
        logFile.flush();

        // Wait 2 seconds before generating next reading
        std::this_thread::sleep_for(
            std::chrono::seconds(2)
        );
    }

    logFile.close();

    std::cout << "\nRobot battery depleted.\n";
    std::cout << "Simulation stopped.\n";

    return 0;
}