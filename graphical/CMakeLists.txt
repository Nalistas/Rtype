cmake_minimum_required(VERSION 3.10)

project(rtype LANGUAGES CXX)

# Configuration standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

# Télécharger et intégrer Raylib
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 4.5.0 # Remplacez par la version souhaitée
)
FetchContent_MakeAvailable(raylib)

# Ajoutez vos fichiers source
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
    main.cpp
    src/Window.cpp
    src/Sprite.cpp
    src/RaySound.cpp
    src/RayMusic.cpp
    src/AudioDevice.cpp
)

# Liez Raylib avec votre projet
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Gestion des plateformes
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _USE_MATH_DEFINES)
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE m pthread dl GL X11)
endif()
