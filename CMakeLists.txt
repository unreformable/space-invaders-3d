cmake_minimum_required(VERSION 3.11)

project(space-invaders-3d)

add_subdirectory(lib)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} glad)