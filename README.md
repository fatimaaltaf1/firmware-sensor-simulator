# 🔧 Sensor Simulator Firmware

[![CI Pipeline](https://github.com/fatimaaltaf1/firmware-sensor-simulator/workflows/CI%20Pipeline/badge.svg)](https://github.com/fatimaaltaf1/firmware-sensor-simulator/actions)

A production-ready embedded C++ firmware project demonstrating professional development practices.

## ✨ Features

- 🎯 **Sensor Simulation**: Temperature & humidity with configurable offsets
- 📡 **Serial Interface**: Command-based protocol (READ, CALIBRATE, OFFSET, STATUS)
- 🔨 **Cross-Platform**: Builds for x86 host and ARM embedded targets
- ✅ **Comprehensive Testing**: Unit tests (GoogleTest) + Hardware-in-Loop tests
- 🚀 **CI/CD Pipeline**: GitHub Actions with parallel stages and caching
- 🐳 **Docker**: ARM toolchain containerization
- 📊 **Code Quality**: clang-format, clang-tidy, coverage reporting

## 🚀 Quick Start
```bash
# Build
cmake -B build
cmake --build build

# Run
./build/sensor_sim

# Test
cd build && ctest --output-on-failure

# HIL Test
pip3 install -r hil/requirements.txt
python3 hil/hil_test.py
```

## 📡 Serial Protocol

| Command | Description | Example Response |
|---------|-------------|------------------|
| `READ` | Get current readings | `TEMP:25.34,HUM:52.18` |
| `CALIBRATE` | Calibrate sensor | `OK: Calibrated` |
| `OFFSET <t> <h>` | Set offsets | `OK: Offset set` |
| `STATUS` | Get health status | `OK: Healthy` |
| `HELP` | Show commands | Command list |

## 🏗️ Project Structure
```
firmware-sensor-sim/
├── src/              # Core firmware (sensor logic, serial interface)
├── test/             # Unit tests with GoogleTest
├── hil/              # Hardware-in-loop Python tests
├── docker/           # ARM toolchain container
├── .github/          # CI/CD pipeline configuration
└── CMakeLists.txt    # Build configuration
```

## 🔨 Building

### Host Build (x86/ARM Mac)
```bash
cmake -B build
cmake --build build
./build/sensor_sim
```

### Cross-Compilation for ARM Embedded
```bash
# Using Docker
docker build -t arm-toolchain docker/
docker run -v $(pwd):/workspace arm-toolchain bash -c \
  "cmake -B build-arm -DCROSS_COMPILE=ON && cmake --build build-arm"

# With local ARM toolchain
cmake -B build-arm -DCROSS_COMPILE=ON
cmake --build build-arm
```

## 🧪 Testing Strategy

### Unit Tests (14 tests)
Tests sensor logic, serial command processing, and edge cases.
```bash
cd build
ctest --output-on-failure
# or
./sensor_tests
```

### Hardware-in-Loop Tests
End-to-end system verification with simulated or real hardware.
```bash
pip3 install -r hil/requirements.txt

# Test with simulated device
python3 hil/hil_test.py

# Test with real serial port
python3 hil/hil_test.py /dev/ttyUSB0
```

### Code Coverage
```bash
cmake -B build -DENABLE_COVERAGE=ON
cmake --build build
cd build && ctest
lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info '/usr/*' '*/test/*' --output-file coverage.info
genhtml coverage.info --output-directory coverage-html
```

## 🚀 CI/CD Pipeline

GitHub Actions pipeline with 5 stages:

1. **Lint & Format** - clang-format, clang-tidy checks
2. **Build & Test** - Host build with unit tests and coverage
3. **Cross-Compile** - ARM build in Docker container
4. **HIL Test** - Automated hardware-in-loop testing
5. **Docker Build** - Toolchain image publishing (on main branch)

Features:
- Parallel execution where possible
- Dependency caching for faster builds
- Artifact uploads (coverage reports, ARM binaries)

## 🛠️ Technologies

- **Language**: C++17
- **Build System**: CMake 3.20+
- **Testing**: GoogleTest, Python (pyserial)
- **Toolchains**: GCC, ARM GCC (arm-none-eabi)
- **CI/CD**: GitHub Actions
- **Containerization**: Docker
- **Code Quality**: clang-format, clang-tidy, lcov

## 📋 Example Session
```
$ ./build/sensor_sim
Sensor Simulator v1.0 (Host Mode)
Type HELP for available commands

> HELP
Commands: READ, CALIBRATE, OFFSET <temp> <hum>, STATUS, HELP

> CALIBRATE
OK: Calibrated

> READ
TEMP:25.12,HUM:51.87

> OFFSET 5 10
OK: Offset set

> READ
TEMP:30.34,HUM:61.92

> STATUS
OK: Healthy
```

## 📝 License

MIT License
