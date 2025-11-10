#include <gtest/gtest.h>
#include "sensor.h"

class SensorTest : public ::testing::Test {
protected:
    Sensor sensor;
};

TEST_F(SensorTest, InitialState) {
    EXPECT_FALSE(sensor.isHealthy());
}

TEST_F(SensorTest, CalibrationMakesHealthy) {
    sensor.calibrate();
    sensor.update();
    EXPECT_TRUE(sensor.isHealthy());
}

TEST_F(SensorTest, TemperatureInRange) {
    sensor.update();
    int16_t temp = sensor.getTemperature();
    EXPECT_GE(temp, 2000);
    EXPECT_LE(temp, 3000);
}

TEST_F(SensorTest, HumidityInRange) {
    sensor.update();
    uint16_t hum = sensor.getHumidity();
    EXPECT_GE(hum, 0);
    EXPECT_LE(hum, 10000);
}

TEST_F(SensorTest, OffsetApplied) {
    sensor.setOffset(500, 1000);
    sensor.update();
    int16_t temp = sensor.getTemperature();
    EXPECT_GE(temp, 2900);
}

TEST_F(SensorTest, MultipleUpdates) {
    for (int i = 0; i < 10; i++) {
        sensor.update();
        EXPECT_GE(sensor.getTemperature(), 2000);
        EXPECT_LE(sensor.getTemperature(), 3000);
    }
}
