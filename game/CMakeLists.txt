project(space-invaders-3d)

set(SRC_FILES
    src/main.cpp
    src/Actor.cpp
    src/Cannon.cpp
    src/Game.cpp
    src/Invader.cpp
    src/InvadersManager.cpp
    src/Laser.cpp
    src/PhysicsSystem.cpp
    src/Wall.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
    src/
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    engine
)