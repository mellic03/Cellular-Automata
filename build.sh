#!/bin/bash
cd ./softrastCPP
./build_library.sh
cd ..
g++ ./src/main.cpp ./softrastCPP/softrast/softrast.a -lSDL2 -std=c++17 -Ofast


