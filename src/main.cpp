#include "sensor.h"
#include "serial_interface.h"
#include <iostream>
#include <string>

int main() {
    Sensor sensor;
    SerialInterface interface(sensor);
    
    std::cout << "Sensor Simulator v1.0 (Host Mode)\n";
    std::cout << "Type HELP for available commands\n";
    
    std::string line;
    while (std::getline(std::cin, line)) {
        std::string response = interface.processCommand(line);
        std::cout << response;
        std::cout.flush();
    }
    
    return 0;
}
