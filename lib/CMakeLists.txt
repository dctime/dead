cmake_minimum_required(VERSION 3.22.1)

project(DEAD_lib)

file(GLOB SOURCES 
  "src/*.cpp"
  "src/map_objects/*.cpp"
  "src/hitbox/*.cpp"
  "src/bullets/*.cpp"
  "src/guns/*.cpp"
  "src/item_drops/*.cpp"
)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main)


