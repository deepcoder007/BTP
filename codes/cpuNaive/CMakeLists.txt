cmake_minimum_required(VERSION 2.6)
project(CPUNAIVE)

set(CMAKE_CXX_FLAGS "-std=c++11 -DDEBUG ")
include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(${CPUNAIVE_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable(CPUNAIVE src/Graph.cpp src/keyValueStore.cpp src/main.cpp)
add_executable(regression src/Graph.cpp src/keyValueStore.cpp src/regression.cpp src/debug.cpp)

