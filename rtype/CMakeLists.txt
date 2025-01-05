cmake_minimum_required(VERSION 3.16)

project(RType
    VERSION 1.0
    DESCRIPTION "RType for Rtype"
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

# Ajouter les fichiers sources specifiques a `RType`
add_executable(RType
    src/main.cpp
    src/Rtype_sc.cpp
    src/RtypeBuilder.cpp
)

# Inclure les fichiers headers
target_include_directories(RType PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link  `common`
target_link_libraries(RType PRIVATE ecs)
target_link_libraries(RType PRIVATE file_selector)
target_link_libraries(RType PRIVATE common_interface)
target_link_libraries(RType PRIVATE protocol)
target_link_libraries(RType PRIVATE graphics_primitives)

if(WIN32)
target_link_libraries(RType PRIVATE ws2_32)
endif()


# Options de compilation
target_compile_options(RType
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
