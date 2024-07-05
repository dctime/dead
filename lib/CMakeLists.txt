cmake_minimum_required(VERSION 3.22.1)

project(DEAD_lib)

add_library(${PROJECT_NAME} src/DEAD_map.cpp)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2main)


