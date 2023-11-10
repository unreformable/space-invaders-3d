project(space-invaders-3d)

set(SRC_FILES
    src/Actor.cpp
    src/Cannon.cpp
    src/Game.cpp
    src/Laser.cpp
    src/PhysicsSystem.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
    src/
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    engine
)