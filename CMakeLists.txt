cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

project(GameEngine VERSION 1.1)

set(LIB_NAME ${PROJECT_NAME})

add_subdirectory(src)

target_include_directories(${LIB_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(tests)

add_dependencies(${PROJECT_NAME}_run ${LIB_NAME}_lib)

target_link_libraries(${PROJECT_NAME}_run ${LIB_NAME}_lib)