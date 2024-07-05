cmake_minimum_required(VERSION 3.22.1)

project(dead)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2main)


