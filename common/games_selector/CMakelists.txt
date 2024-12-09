cmake_minimum_required(VERSION 3.15)

# Nom du projet
project(file_selector LANGUAGES CXX)

# Définit la version de C++ à utiliser
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ajoute les répertoires include
include_directories(include)

# Crée une bibliothèque statique (changer le nom de "myfile_selector" en "file_selector")
add_library(file_selector STATIC
    src/IDirectoryLister.cpp
    src/SafeDirectoryLister.cpp
)

# Ajoute les répertoires include au projet
target_include_directories(file_selector
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Option pour activer les warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(file_selector PRIVATE -Wall -Wextra -pedantic)
endif()
