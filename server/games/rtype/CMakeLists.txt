project(r-type)

add_library(${PROJECT_NAME} SHARED
    src/entry_point.cpp
    src/RType.cpp
    src/Handlers/MoveHandlers.cpp
    src/Handlers/ShootHandlers.cpp
    src/Systems/SystemMovement.cpp
    src/Systems/SystemCreateEnemy.cpp
    src/Systems/SystemCollision.cpp
    src/Systems/SystemBroadcast.cpp
    src/Systems/SystemShootEnemyBullet.cpp
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
