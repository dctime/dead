cmake_minimum_required(VERSION 3.22.1)

project(DEAD_lib)

file(GLOB SOURCES 
  "src/*.cpp"
  "src/map_objects/*.cpp"
  "src/hitbox/*.cpp"
  "src/bullets/*.cpp"
  "src/guns/*.cpp"
  "src/item_drops/*.cpp"
  "src/zombies/*.cpp"
  "src/ui/*.cpp"
  "src/weapons/*.cpp"
  "src/particles/*.cpp"
  "src/items/*.cpp"
  "src/decorations/*.cpp"
  "src/subrenderers/*.cpp"
)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_ttf SDL2_mixer)


