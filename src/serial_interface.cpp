#include "serial_interface.h"
#include <sstream>
#include <iomanip>

SerialInterface::SerialInterface(Sensor& sensor) : sensor_(sensor) {}

std::string SerialInterface::processCommand(const std::string& cmd) {
    std::string trimmed = cmd;
    size_t end = trimmed.find_last_not_of(" \t\r\n");
    if (end != std::string::npos) {
        trimmed = trimmed.substr(0, end + 1);
    }
    
    if (trimmed == "READ") {
        return handleRead();
    } else if (trimmed == "CALIBRATE") {
        return handleCalibrate();
    } else if (trimmed.find("OFFSET") == 0) {
        return handleSetOffset(trimmed.substr(6));
    } else if (trimmed == "STATUS") {
        return handleStatus();
    } else if (trimmed == "HELP") {
        return handleHelp();
    }
    
    return "ERROR: Unknown command\n";
}

std::string SerialInterface::handleRead() {
    sensor_.update();
    std::ostringstream oss;
    oss << "TEMP:" << std::fixed << std::setprecision(2) 
        << (sensor_.getTemperature() / 100.0) << ",";
    oss << "HUM:" << std::fixed << std::setprecision(2)
        << (sensor_.getHumidity() / 100.0) << "\n";
    return oss.str();
}

std::string SerialInterface::handleCalibrate() {
    sensor_.calibrate();
    return "OK: Calibrated\n";
}

std::string SerialInterface::handleSetOffset(const std::string& args) {
    std::istringstream iss(args);
    int temp, hum;
    
    if (iss >> temp >> hum) {
        sensor_.setOffset(static_cast<int16_t>(temp * 100), 
                         static_cast<int16_t>(hum * 100));
        return "OK: Offset set\n";
    }
    return "ERROR: Invalid offset format\n";
}

std::string SerialInterface::handleStatus() {
    return sensor_.isHealthy() ? "OK: Healthy\n" : "ERROR: Not calibrated\n";
}

std::string SerialInterface::handleHelp() {
    return "Commands: READ, CALIBRATE, OFFSET <temp> <hum>, STATUS, HELP\n";
}
