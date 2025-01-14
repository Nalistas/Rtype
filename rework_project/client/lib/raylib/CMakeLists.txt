cmake_minimum_required(VERSION 3.15)

# Nom du projet
project(cppray LANGUAGES CXX)

# Définit la version de C++ à utiliser
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ajout des définitions spécifiques
add_compile_definitions(WIN32_LEAN_AND_MEAN NOMINMAX)

# Télécharger et intégrer Raylib via FetchContent
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 4.5.0
)
FetchContent_MakeAvailable(raylib)

# Ajoute les répertoires include pour votre encapsulation
include_directories(include)

# Crée une bibliothèque statique pour votre encapsulation de Raylib
add_library(cppray STATIC
    src/AudioDevice.cpp
    src/RayMusic.cpp
    src/RaySound.cpp
    src/Sprite.cpp
    src/TextureManager.cpp
    src/Window.cpp
    src/RayText.cpp
)

# Cible les répertoires include
target_include_directories(cppray
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Lien avec Raylib
target_link_libraries(cppray
    PUBLIC
        raylib
)

# Active les warnings (GCC/Clang uniquement)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(cppray PRIVATE -Wall -Wextra -pedantic)
endif()
