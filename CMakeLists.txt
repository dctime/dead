cmake_minimum_required(VERSION 3.22.1)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -rdynamic")

project(dead)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
set(CMAKE_C_STANDARD 20)
include_directories (${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})


add_subdirectory(lib)

add_executable(${PROJECT_NAME} main.cpp)

add_definitions(${GTK3_CFLAGS_OTHER})

add_custom_target(copy_folders ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory 
  ${PROJECT_SOURCE_DIR}/assets
  ${PROJECT_BINARY_DIR}/assets
  COMMENT "Copy Assets to build ..."
)

add_dependencies(dead copy_folders)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/include)


target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/src)
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main DEAD_lib SDL2_image mysqlcppconn)
target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES})




