add_subdirectory(lib)

set(SRC_FILES
    src/Graphics.cpp
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