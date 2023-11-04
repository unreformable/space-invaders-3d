cmake_minimum_required(VERSION 3.11)

project(space-invaders-3d)

add_subdirectory(lib)

set(SRC_FILES
    src/main.cpp
    src/Bitmap3D.cpp
    src/Camera.cpp
    src/Invaders.cpp
    src/LaserCannon.cpp
    src/Mesh.cpp
    src/Program.cpp
    src/Utils.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    glad
    glm
    SDL2-static
    SDL2main
)