cmake_minimum_required(VERSION 3.22.1)

project(dead)

add_subdirectory(lib)

add_executable(${PROJECT_NAME} main.cpp)

add_custom_target(copy_folders ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory 
  ${PROJECT_SOURCE_DIR}/data
  ${PROJECT_BINARY_DIR}/data
  COMMENT "Copy Folders to build ..."
)

add_dependencies(dead copy_folders)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/include)
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/src)
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main DEAD_lib)


