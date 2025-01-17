project(r-type)

add_library(${PROJECT_NAME} SHARED
    src/entry_point.cpp
    src/RType.cpp
    src/Handlers/MoveHandlers.cpp
    src/Systems/SystemMovement.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    asio_server
    ecs
    game_interface
)

target_compile_definitions(${PROJECT_NAME} PRIVATE MY_GAME_DEFINITION=1)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/games)
