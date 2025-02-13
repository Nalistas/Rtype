cmake_minimum_required(VERSION 3.15)

project(asio_server LANGUAGES CXX)

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

add_library(asio_server STATIC
    src/TcpServer.cpp
    src/UdpServer.cpp
)

target_include_directories(asio_server
    PUBLIC
        ${asio_SOURCE_DIR}/asio/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (WIN32)
    target_link_libraries(asio_server ws2_32)
endif()
