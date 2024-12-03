cmake_minimum_required(VERSION 3.16)

project(Server
    VERSION 1.0
    DESCRIPTION "Server for Rtype"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)


# Download and build ASIO
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-18-2
)
FetchContent_MakeAvailable(asio)
include_directories(${asio_SOURCE_DIR}/asio/include)


# Compose the project
add_executable(Server)
target_include_directories(Server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_sources(Server
    PRIVATE
    src/main.cpp
    src/Server.cpp
    src/IDirectoryLister.cpp
    src/SafeDirectoryLister.cpp
    src/Thread/ScopeLock.cpp
    src/Thread/Mutex.cpp
    src/Thread/ConditionVariable.cpp
)


target_link_libraries(Server PRIVATE ecs)
target_include_directories(Server PRIVATE ${CMAKE_SOURCE_DIR}/ecs)


target_compile_options(Server
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
