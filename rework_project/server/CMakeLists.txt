cmake_minimum_required(VERSION 3.15)

project(r-type_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(r-type_server)


target_include_directories(r-type_server
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(r-type_server
    PRIVATE
        src/main.cpp
        src/RoomsCore.cpp
        src/GameCore.cpp
)

add_subdirectory(lib/asio_server)
add_subdirectory(lib/ecs)
add_subdirectory(lib/files_selector)
add_subdirectory(lib/interface)
add_subdirectory(games/rtype)

target_link_libraries(r-type_server PRIVATE asio_server)
target_link_libraries(r-type_server PRIVATE ecs)
target_link_libraries(r-type_server PRIVATE file_selector)
target_link_libraries(r-type_server PRIVATE game_interface)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(r-type_server PRIVATE -Wall -Wextra -pedantic)
endif()
