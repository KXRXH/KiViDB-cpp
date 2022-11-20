#!/usr/bin/env bash

mkdir include
cd include || exit
curl -LO https://github.com/CrowCpp/Crow/releases/download/v1.0%2B5/crow_all.h
cd ..
mkdir build
cd build || exit
cmake ..
cmake --build .