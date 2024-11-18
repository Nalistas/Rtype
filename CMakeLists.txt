cmake_minimum_required(VERSION 3.16)
project(MainTest)

# Activer le support C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ajouter le fichier source
add_executable(MainTest main.cpp)
