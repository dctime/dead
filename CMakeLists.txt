cmake_minimum_required(VERSION 3.22.1)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -rdynamic")

project(dead)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(lib)

add_executable(${PROJECT_NAME} main.cpp)


add_custom_target(copy_assets ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory 
  ${PROJECT_SOURCE_DIR}/assets
  ${PROJECT_BINARY_DIR}/assets
  COMMENT "Copy Assets to build ..."
)

add_dependencies(dead copy_assets)

add_custom_target(copy_quotes ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory 
  ${PROJECT_SOURCE_DIR}/quotes
  ${PROJECT_BINARY_DIR}/quotes
  COMMENT "Copy Quotes to build ..."
)

add_dependencies(dead copy_quotes)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/include)


target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/src)
target_link_libraries(${PROJECT_NAME} DEAD_lib)




