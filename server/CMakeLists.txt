cmake_minimum_required(VERSION 3.16)

project(Server
    VERSION 1.0
    DESCRIPTION "Server for Rtype"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-18-2
)
FetchContent_MakeAvailable(asio)

include_directories(${asio_SOURCE_DIR}/asio/include)

add_executable(Server)


target_sources(Server
    PRIVATE
    main.cpp
    Server.cpp
)

target_compile_options(Server
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
