add_subdirectory(lib)

set(SRC_FILES
    src/Bitmap3D.cpp
    src/Graphics.cpp
    src/Input.cpp
    src/Mesh.cpp
    src/Program.cpp
    src/RNG.cpp
    src/Utils.cpp
)

add_library(engine STATIC ${SRC_FILES})

target_include_directories(engine
    PUBLIC
    src/
)

target_link_libraries(engine
    PUBLIC
    glad
    glm
    SDL2-static
    SDL2main
)