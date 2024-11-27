cmake_minimum_required(VERSION 3.15)

# Nom du projet
project(ecs LANGUAGES CXX)

# Définit la version de C++ à utiliser
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ajoute les répertoires include
include_directories(include)

# Crée un exécutable pour le projet
add_executable(${PROJECT_NAME} main.cpp)

# Ajoute les fichiers source au projet
target_sources(${PROJECT_NAME}
    PRIVATE
        src/entity.cpp
        src/registry.cpp
)

# Ajoute les répertoires include au projet
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include # Répertoire include spécifique
)

# Option pour activer les warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()
