cmake_minimum_required(VERSION 3.22.1)

project(dead)

add_subdirectory(lib)
add_subdirectory(json)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/include)
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/src)
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main DEAD_lib nlohmann_json)


