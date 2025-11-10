# Sensor Simulator Firmware

A toy C++ firmware application with CI/CD, testing, and HIL simulation.

## Quick Start
```bash
# Build
cmake -B build
cmake --build build

# Run
./build/sensor_sim

# Test
cd build && ctest
```

## Commands

- `READ` - Get sensor readings
- `CALIBRATE` - Calibrate sensor
- `OFFSET <temp> <hum>` - Set offsets
- `STATUS` - Get status
- `HELP` - Show help
