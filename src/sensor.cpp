#include "sensor.h"
#include <cmath>
#include <cstdlib>

Sensor::Sensor()
    : temperature_(2500), humidity_(5000), temp_offset_(0), 
      humidity_offset_(0), is_calibrated_(false), read_count_(0) {}

void Sensor::update() {
    int16_t noise = (rand() % 200) - 100;
    temperature_ = 2500 + noise + temp_offset_;
    
    noise = (rand() % 400) - 200;
    humidity_ = 5000 + noise + humidity_offset_;
    
    if (humidity_ > 10000) humidity_ = 10000;
    if (humidity_ < 0) humidity_ = 0;
    
    read_count_++;
}

int16_t Sensor::getTemperature() const {
    return temperature_;
}

uint16_t Sensor::getHumidity() const {
    return humidity_;
}

bool Sensor::isHealthy() const {
    return is_calibrated_ && read_count_ > 0;
}

void Sensor::calibrate() {
    is_calibrated_ = true;
    temp_offset_ = 0;
    humidity_offset_ = 0;
}

void Sensor::setOffset(int16_t temp_offset, int16_t humidity_offset) {
    temp_offset_ = temp_offset;
    humidity_offset_ = humidity_offset;
}
