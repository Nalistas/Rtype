cmake_minimum_required(VERSION 3.16)

project(Rtype
    VERSION 1.0
    DESCRIPTION "Game Rtype"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Compose the project
add_library(Rtype SHARED) # Création de la bibliothèque partagée
target_include_directories(Rtype PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(Rtype PRIVATE
    ${CMAKE_SOURCE_DIR}/common/interface
    ${CMAKE_SOURCE_DIR}/common/ecs/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(Rtype
    PRIVATE
        entrypoints.cpp
        src/Rtype.cpp
        src/RtypePlayer.cpp
)

target_compile_options(Rtype
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
