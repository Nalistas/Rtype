cmake_minimum_required(VERSION 3.16)

project(Client
    VERSION 1.0
    DESCRIPTION "Client for Rtype"
    LANGUAGES CXX
)

# Configuration standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_definitions(WIN32_LEAN_AND_MEAN NOMINMAX)

# Télécharger et intégrer Raylib via FetchContent
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 4.5.0
)
FetchContent_MakeAvailable(raylib)

# Télécharger et intégrer ASIO via FetchContent
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-18-2
)
FetchContent_MakeAvailable(asio)
include_directories(${asio_SOURCE_DIR}/asio/include)

# Définir l'exécutable
add_executable(Client)
target_include_directories(Client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Ajouter les sources
target_sources(Client
    PRIVATE
        main.cpp
        src/Raylib/Window.cpp
        src/Raylib/Sprite.cpp
        src/Raylib/RaySound.cpp
        src/Raylib/RayMusic.cpp
        src/Raylib/AudioDevice.cpp
        src/Background.cpp
        src/GraphicalCore.cpp
        src/Core.cpp
        src/Systems/SystemBackground.cpp
        src/Systems/SystemTime.cpp
        src/Systems/SystemSprite.cpp
)

# Lier les bibliothèques
target_link_libraries(Client PRIVATE raylib)
target_link_libraries(Client PRIVATE ecs)
target_link_libraries(Client PRIVATE protocol)

# Ajouter les répertoires d'inclusion pour ecs
target_include_directories(Client PRIVATE ${CMAKE_SOURCE_DIR}/common/ecs)

# Options de compilation
target_compile_options(Client
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

# Configuration spécifique aux plateformes
if(WIN32)
    target_compile_definitions(Client PRIVATE _USE_MATH_DEFINES)
    target_link_libraries(Client PRIVATE Ws2_32)  # Lier la bibliothèque Winsock
elseif(APPLE)
    target_link_libraries(Client PRIVATE "-framework OpenGL")
elseif(UNIX)
    target_link_libraries(Client PRIVATE m pthread dl GL X11)
endif()
