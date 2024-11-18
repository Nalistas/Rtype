# Minimum requis pour utiliser les fonctionnalités modernes de CMake
cmake_minimum_required(VERSION 3.16)

# Définir le nom du projet et sa version
project(MainTest
    VERSION 1.0            # Version du projet
    DESCRIPTION "Simple C++ project using CMake" # Brève description
    LANGUAGES CXX          # Langage utilisé (C++)
)

# Activer le support du standard C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(MainTest)

target_sources(MainTest
    PRIVATE
        main.cpp
        hello.cpp
)

target_include_directories(MainTest
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR} # Répertoire actuel
)

# Ajout de définitions conditionnelles pour Windows/Linux
if (WIN32)
    target_compile_definitions(MainTest PRIVATE PLATFORM_WINDOWS)
elseif(UNIX)
    target_compile_definitions(MainTest PRIVATE PLATFORM_LINUX)
endif()

# Configuration des options de compilation
target_compile_options(MainTest
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

# Messages d'information pour débogage
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
