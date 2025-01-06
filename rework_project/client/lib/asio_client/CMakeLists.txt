cmake_minimum_required(VERSION 3.15)

# Nom du projet
project(asio_client LANGUAGES CXX)

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


# Ajouter les répertoires include
include_directories(include)

# Crée une bibliothèque statique pour le projet Asio
add_library(asio_client STATIC
    src/TcpClient.cpp
    src/UdpClient.cpp
)

# Ajouter les répertoires include pour la bibliothèque
target_include_directories(asio_client
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
