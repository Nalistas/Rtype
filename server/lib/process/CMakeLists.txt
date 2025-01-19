cmake_minimum_required(VERSION 3.15)

project(process LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_library(process STATIC
    src/Process.cpp
)

target_include_directories(process
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(process PRIVATE -Wall -Wextra -pedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(process PRIVATE /W4)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(process PRIVATE -fno-common) # Important pour les définitions multiples
endif()

set_target_properties(process PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
