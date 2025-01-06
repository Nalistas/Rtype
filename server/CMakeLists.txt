cmake_minimum_required(VERSION 3.16)

project(r-type_server
    VERSION 1.0
    DESCRIPTION "r-type_server for Rtype"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# Télécharger et inclure ASIO
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-18-2
)
FetchContent_MakeAvailable(asio)
include_directories(${asio_SOURCE_DIR}/asio/include)

# Ajouter les fichiers sources specifiques a `r-type_server`
add_executable(r-type_server
    src/main.cpp
    src/Server.cpp
    src/Thread/ScopeLock.cpp
    src/Thread/Mutex.cpp
    src/Thread/ConditionVariable.cpp
    src/Systems/SystemGraphicSpriteSpeed.cpp
    src/Systems/SystemTime.cpp
)

# Inclure les fichiers headers
target_include_directories(r-type_server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link  `common`
target_link_libraries(r-type_server PRIVATE ecs)
target_link_libraries(r-type_server PRIVATE file_selector)
target_link_libraries(r-type_server PRIVATE common_interface)
target_link_libraries(r-type_server PRIVATE protocol)
target_link_libraries(r-type_server PRIVATE graphics_primitives)

if(WIN32)
target_link_libraries(r-type_server PRIVATE ws2_32)
endif()


# Options de compilation
target_compile_options(r-type_server
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
