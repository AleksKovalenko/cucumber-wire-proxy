cmake_minimum_required(VERSION 3.24)

project(cucumber_test VERSION 4.11.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

option(CMAKE_COMPILE_WARNING_AS_ERROR "Enable warnings-as-error" On)
option(CN_ENABLE_COVERAGE "Enable compiler flags for code coverage measurements" Off)

add_definitions(-DMEMP_NUM_UDP_PCB=10)

add_subdirectory(amp-embedded-infra-lib)

add_subdirectory(echo_instantiation)
add_subdirectory(step_implementations)
add_subdirectory(cucumber_wire_proxy)
