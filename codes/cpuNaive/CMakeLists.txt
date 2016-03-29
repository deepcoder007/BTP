cmake_minimum_required(VERSION 2.6)
project(cpuNaive)

include_directories('${PROJECT_BINARY_DIR}/include')
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable(cpuNaive src/cpuNaive.cpp)

