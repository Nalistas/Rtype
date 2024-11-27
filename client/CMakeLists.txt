cmake_minimum_required(VERSION 3.16)

project(MainTest
    VERSION 1.0
    DESCRIPTION "Simple C++ project using CMake"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include(FetchContent)
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-18-2
)

FetchContent_MakeAvailable(asio)

include_directories(${asio_SOURCE_DIR}/asio/include)

add_executable(MainTest)

target_include_directories(MainTest
    PRIVATE
        asio
)

target_sources(MainTest
    PRIVATE
        main.cpp
        Client.cpp
)

target_compile_options(MainTest
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
