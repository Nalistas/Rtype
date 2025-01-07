cmake_minimum_required(VERSION 3.15)

# Nom du projet
project(file_selector LANGUAGES CXX)

# Définit la version de C++ à utiliser
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ajoute les répertoires include
include_directories(include)

# Crée une bibliothèque statique
add_library(file_selector STATIC
    src/IDirectoryLister.cpp
    src/DLLoaderException.cpp  # Corrigez l'orthographe si nécessaire
    src/SafeDirectoryLister.cpp
)

# Ajoute les répertoires include au projet
target_include_directories(file_selector
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Option pour activer les warnings en fonction du compilateur
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(file_selector PRIVATE -Wall -Wextra -pedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(file_selector PRIVATE /W4)
endif()

# Ajout des options pour éviter les conflits de symboles
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(file_selector PRIVATE -fno-common) # Important pour les définitions multiples
endif()

# Génère automatiquement une liste des dépendances
set_target_properties(file_selector PROPERTIES
    POSITION_INDEPENDENT_CODE ON # Rend compatible avec les bibliothèques partagées
)

