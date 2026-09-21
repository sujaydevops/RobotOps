#ifndef TELEMETRY_LOGGER_H
#define TELEMETRY_LOGGER_H

#include <string>
#include "Robot.h"

class TelemetryLogger {
private:
    std::string filename;

public:
    explicit TelemetryLogger(const std::string& filename);

    void initialize();
    void log(const Robot& robot);
};

#endif
