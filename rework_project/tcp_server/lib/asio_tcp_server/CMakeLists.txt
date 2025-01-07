cmake_minimum_required(VERSION 3.15)

project(asio_client LANGUAGES CXX)

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

# Utiliser target_include_directories pour exposer les chemins vers Asio
add_library(asio_client STATIC
    src/TcpServer.cpp
)

# Assure que le répertoire d'inclusion d'Asio est bien ajouté à ton projet
target_include_directories(asio_client
    PUBLIC
        ${asio_SOURCE_DIR}/asio/include  # Inclure Asio dans le module
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(test
    main.cpp
)

target_link_libraries(test
    asio_client
)
