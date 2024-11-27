cmake_minimum_required(VERSION 3.16)

# Nom du projet
project(rtype LANGUAGES CXX VERSION 1.0 DESCRIPTION "C++ Project combining Raylib and ASIO")

# Configuration standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Directories pour les includes
include_directories(include)

# Télécharger et intégrer Raylib via FetchContent
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 4.5.0 # Remplacez par la version souhaitée
)
FetchContent_MakeAvailable(raylib)

# Télécharger et intégrer ASIO via FetchContent
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-18-2
)
FetchContent_MakeAvailable(asio)

# Ajouter les répertoires d'inclusion pour ASIO
include_directories(${asio_SOURCE_DIR}/asio/include)

# Définir l'exécutable principal
add_executable(${PROJECT_NAME})

# Ajouter les fichiers sources pour l'exécutable
target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
        src/Window.cpp
        src/Sprite.cpp
        Client.cpp
)

# Lier les bibliothèques avec l'exécutable
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Ajouter des options de compilation
target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

# Plateformes spécifiques
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _USE_MATH_DEFINES)
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE m pthread dl GL X11)
endif()

# Afficher des informations sur le projet
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
