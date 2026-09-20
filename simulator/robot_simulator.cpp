#include <iostream>
#include <iomanip>
#include <random>
#include <thread>
#include <chrono>

struct RobotTelemetry {
    int robotId;
    double battery;
    double temperature;
    double speed;
    double xPosition;
    double yPosition;
};

int main() {

    RobotTelemetry robot{
        1,
        100.0,
        35.0,
        0.0,
        0.0,
        0.0
    };

    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_real_distribution<double> temperatureChange(-0.5, 0.8);
    std::uniform_real_distribution<double> speedChange(0.0, 2.5);
    std::uniform_real_distribution<double> movement(-1.0, 1.0);

    std::cout << "=============================\n";
    std::cout << "     ROBOTOPS SIMULATOR\n";
    std::cout << "=============================\n\n";

    while (robot.battery > 0) {

        robot.battery -= 0.5;

        robot.temperature += temperatureChange(generator);
        robot.speed = speedChange(generator);

        robot.xPosition += movement(generator);
        robot.yPosition += movement(generator);

        std::string status = "NORMAL";

        if (robot.temperature > 45.0) {
            status = "WARNING";
        }

        if (robot.temperature > 50.0) {
            status = "CRITICAL";
        }

        std::cout << std::fixed << std::setprecision(2);

        std::cout << "Robot: RBT-"
                  << std::setw(3)
                  << std::setfill('0')
                  << robot.robotId
                  << std::setfill(' ')
                  << "\n";

        std::cout << "Battery: "
                  << robot.battery
                  << "%\n";

        std::cout << "Temperature: "
                  << robot.temperature
                  << " C\n";

        std::cout << "Speed: "
                  << robot.speed
                  << " m/s\n";

        std::cout << "Position: ("
                  << robot.xPosition
                  << ", "
                  << robot.yPosition
                  << ")\n";

        std::cout << "Status: "
                  << status
                  << "\n";

        std::cout << "-----------------------------\n";

        std::this_thread::sleep_for(
            std::chrono::seconds(2)
        );
    }

    std::cout << "Robot battery depleted.\n";
    std::cout << "Simulation stopped.\n";

    return 0;
}
