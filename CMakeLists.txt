# Minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(MainProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the ecs library as a subdirectory
add_subdirectory(ecs)

# Add the main executable
add_executable(main main.cpp)

# Link the ecs library to the main executable
target_link_libraries(main PRIVATE ecs)

# Include headers from the ecs library
target_include_directories(main PRIVATE ecs/include)
