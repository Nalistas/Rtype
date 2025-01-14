cmake_minimum_required(VERSION 3.15)

project(game_interface LANGUAGES CXX)

add_library(game_interface INTERFACE)

target_include_directories(game_interface
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

