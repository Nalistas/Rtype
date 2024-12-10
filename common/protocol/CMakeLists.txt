cmake_minimum_required(VERSION 3.15)

# Nom du projet
project(protocol LANGUAGES CXX)

# Définit la version de C++ à utiliser
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include(FetchContent)

FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-18-2
)
FetchContent_MakeAvailable(asio)
include_directories(${asio_SOURCE_DIR}/asio/include)




# Ajoute les répertoires include
include_directories(include)

# Crée une bibliothèque statique (changer le nom de "myprotocol" en "protocol")
add_library(protocol STATIC
    src/Encoder.cpp
    src/AsioApi.cpp
)

# Ajoute les répertoires include au projet
target_include_directories(protocol
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Option pour activer les warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(protocol PRIVATE -Wall -Wextra -pedantic)
endif()
