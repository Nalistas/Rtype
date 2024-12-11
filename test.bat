@echo off
mkdir build
cmake -G "MinGW Makefiles" -S . -B build
cmake --build build
pause
