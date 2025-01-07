
project(r-type_udp_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(r-type_udp_server)


target_include_directories(r-type_udp_server
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(r-type_udp_server
    PRIVATE
        src/main.cpp
)

add_subdirectory(lib/asio_udp_server)
add_subdirectory(lib/ecs)
add_subdirectory(lib/files_selector)

target_link_libraries(r-type_udp_server PRIVATE asio_udp_server)
target_link_libraries(r-type_udp_server PRIVATE ecs)
target_link_libraries(r-type_udp_server PRIVATE file_selector)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(r-type_udp_server PRIVATE -Wall -Wextra -pedantic)
endif()
