#include <gtest/gtest.h>
#include "serial_interface.h"
#include "sensor.h"

class SerialInterfaceTest : public ::testing::Test {
protected:
    Sensor sensor;
    SerialInterface interface{sensor};
};

TEST_F(SerialInterfaceTest, HelpCommand) {
    std::string response = interface.processCommand("HELP");
    EXPECT_NE(response.find("Commands"), std::string::npos);
}

TEST_F(SerialInterfaceTest, CalibrateCommand) {
    std::string response = interface.processCommand("CALIBRATE");
    EXPECT_EQ(response, "OK: Calibrated\n");
}

TEST_F(SerialInterfaceTest, StatusAfterCalibration) {
    interface.processCommand("CALIBRATE");
    sensor.update();
    std::string response = interface.processCommand("STATUS");
    EXPECT_EQ(response, "OK: Healthy\n");
}

TEST_F(SerialInterfaceTest, ReadCommand) {
    std::string response = interface.processCommand("READ");
    EXPECT_NE(response.find("TEMP:"), std::string::npos);
    EXPECT_NE(response.find("HUM:"), std::string::npos);
}

TEST_F(SerialInterfaceTest, OffsetCommand) {
    std::string response = interface.processCommand("OFFSET 5 10");
    EXPECT_EQ(response, "OK: Offset set\n");
}

TEST_F(SerialInterfaceTest, InvalidOffsetCommand) {
    std::string response = interface.processCommand("OFFSET invalid");
    EXPECT_NE(response.find("ERROR"), std::string::npos);
}

TEST_F(SerialInterfaceTest, UnknownCommand) {
    std::string response = interface.processCommand("INVALID");
    EXPECT_NE(response.find("ERROR"), std::string::npos);
}
