cmake_minimum_required(VERSION 3.20)
project(SensorSimulator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
option(CROSS_COMPILE "Cross compile for ARM" OFF)

if(CROSS_COMPILE)
    set(CMAKE_SYSTEM_NAME Generic)
    set(CMAKE_SYSTEM_PROCESSOR arm)
    set(CMAKE_C_COMPILER arm-none-eabi-gcc)
    set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
    add_definitions(-DARM_TARGET)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
if(ENABLE_COVERAGE AND NOT CROSS_COMPILE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

set(SOURCES
    src/sensor.cpp
    src/serial_interface.cpp
)

add_executable(sensor_sim src/main.cpp ${SOURCES})
target_include_directories(sensor_sim PRIVATE src)

if(NOT CROSS_COMPILE)
    enable_testing()
    
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    
    add_executable(sensor_tests
        test/test_sensor.cpp
        test/test_serial.cpp
        ${SOURCES}
    )
    target_include_directories(sensor_tests PRIVATE src)
    target_link_libraries(sensor_tests GTest::gtest_main)
    
    include(GoogleTest)
    gtest_discover_tests(sensor_tests)
endif()

install(TARGETS sensor_sim DESTINATION bin)
