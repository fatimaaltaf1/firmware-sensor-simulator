#ifndef SERIAL_INTERFACE_H
#define SERIAL_INTERFACE_H

#include <string>
#include "sensor.h"

class SerialInterface {
public:
    explicit SerialInterface(Sensor& sensor);
    std::string processCommand(const std::string& cmd);
    
private:
    Sensor& sensor_;
    std::string handleRead();
    std::string handleCalibrate();
    std::string handleSetOffset(const std::string& args);
    std::string handleStatus();
    std::string handleHelp();
};

#endif // SERIAL_INTERFACE_H
