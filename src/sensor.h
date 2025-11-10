#ifndef SENSOR_H
#define SENSOR_H

#include <cstdint>

class Sensor {
public:
    Sensor();
    void update();
    int16_t getTemperature() const;
    uint16_t getHumidity() const;
    bool isHealthy() const;
    void calibrate();
    void setOffset(int16_t temp_offset, int16_t humidity_offset);
    
private:
    int16_t temperature_;
    uint16_t humidity_;
    int16_t temp_offset_;
    int16_t humidity_offset_;
    bool is_calibrated_;
    uint32_t read_count_;
};

#endif // SENSOR_H
