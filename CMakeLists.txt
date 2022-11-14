cmake_minimum_required(VERSION 3.23)
project(KiViDB-cpp)

set(CMAKE_CXX_STANDARD 23)
FILE(GLOB SrcCpp src/main.cpp)

FILE(GLOB SrcCore src/core/*.cpp src/core/*.hpp)
FILE(GLOB SrcDt src/datatypes/*.cpp src/datatypes/*.hpp)

add_executable(KiViDB-cpp ${SrcCore} ${SrcCpp} ${SrcDt})
