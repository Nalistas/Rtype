cmake_minimum_required(VERSION 3.15)

# Nom du projet
project(ECSProject LANGUAGES CXX)

# Définit la version de C++ à utiliser
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ajoute les répertoires include et src
include_directories(include)

# Crée un exécutable pour le projet
add_executable(ECSProject ${SOURCES} ${HEADERS})

target_sources(ECSProject
    PRIVATE
    src/entity.cpp
    src/registry.cpp
    main.cpp
)

target_include_directories(ECSProject
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR} # Répertoire actuel
)

# Option pour activer les warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(ECSProject PRIVATE -Wall -Wextra -pedantic)
endif()
