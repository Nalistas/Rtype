cmake_minimum_required(VERSION 3.15)

project(asio_udp_server LANGUAGES CXX)

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

add_library(asio_udp_server STATIC
    src/UdpServer.cpp
)

target_include_directories(asio_udp_server
    PUBLIC
        ${asio_SOURCE_DIR}/asio/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
