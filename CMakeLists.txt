cmake_minimum_required(VERSION 3.23)
project(KiViDB-cpp)

set(CMAKE_CXX_STANDARD 20)
FILE(GLOB SrcCpp src/main.cpp)

FILE(GLOB SrcCore src/core/*.cpp src/core/*.hpp)
FILE(GLOB SrcApi src/api/*.cpp src/api/*.hpp)
FILE(GLOB SrcDt src/datatypes/*.cpp src/datatypes/*.hpp)

include_directories(KiViDB-cpp PRIVATE include/)

add_executable(KiViDB-cpp ${SrcCore} ${SrcCpp} ${SrcDt} test/tests.hpp ${SrcApi})
