#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "Robot.h"
#include "TelemetryLogger.h"

int main() {
    std::cout << "====================================\n";
    std::cout << "        ROBOTOPS MONITOR v1.0       \n";
    std::cout << "====================================\n\n";

    std::vector<Robot> robots;

    robots.emplace_back("RBT-001");
    robots.emplace_back("RBT-002");
    robots.emplace_back("RBT-003");
    robots.emplace_back("RBT-004");
    robots.emplace_back("RBT-005");

    TelemetryLogger logger("telemetry.csv");
    logger.initialize();

    std::cout << "Monitoring 5 robots...\n";
    std::cout << "Press Ctrl+C to stop.\n\n";

    while (true) {

        std::cout << "------------------------------------\n";

        for (Robot& robot : robots) {

            robot.update();
            robot.evaluateHealth();

            logger.log(robot);

            std::cout
                << robot.getId()
                << " | " << robot.getStatus()
                << " | Battery: " << robot.getBattery() << "%"
                << " | Temp: " << robot.getTemperature() << " C"
                << " | Speed: " << robot.getSpeed() << " m/s";

            if (robot.getErrorCode() != "NONE") {
                std::cout << " | ERROR: "
                          << robot.getErrorCode();
            }

            std::cout << '\n';
        }

        std::cout << "------------------------------------\n\n";

        std::this_thread::sleep_for(
            std::chrono::seconds(2)
        );
    }

    return 0;
}

