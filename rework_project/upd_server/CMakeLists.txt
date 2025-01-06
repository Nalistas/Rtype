cmake_minimum_required(VERSION 3.15)

project(upd_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(r-type_udp_server)

add_subdirectory(lib/ecs)
add_subdirectory(lib/files_selector)

