cmake_minimum_required(VERSION 3.15)

project(file_selector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_library(file_selector STATIC
    src/IDirectoryLister.cpp
    src/DLLoaderException.cpp
    src/SafeDirectoryLister.cpp
)

target_include_directories(file_selector
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(file_selector PRIVATE -Wall -Wextra -pedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(file_selector PRIVATE /W4)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(file_selector PRIVATE -fno-common) # Important pour les définitions multiples
endif()

set_target_properties(file_selector PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

