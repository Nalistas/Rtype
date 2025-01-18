cmake_minimum_required(VERSION 3.15)

project(r-type_client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(r-type_client)

# Ajouter les sous-répertoires (Asio et raylib)
add_subdirectory(lib/asio_client)
add_subdirectory(lib/raylib)

target_link_libraries(r-type_client PRIVATE asio_client)
target_link_libraries(r-type_client PRIVATE cppray)

target_include_directories(r-type_client
    PRIVATE
        include
)

target_sources(r-type_client
    PRIVATE
        src/main.cpp
        src/Core.cpp
        src/ClientRoom.cpp
        src/Login.cpp
        src/Background.cpp
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(r-type_client PRIVATE -Wall -Wextra -pedantic)
endif()
