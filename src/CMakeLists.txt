set(BINARY ${CMAKE_PROJECT_NAME})

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.h *.cpp *.c)

add_executable(${BINARY}_run ${SOURCES})

set_property(TARGET ${BINARY}_run PROPERTY CXX_STANDARD 17)

add_library(${BINARY}_lib STATIC ${SOURCES})

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${glfw3_INCLUE_DIRS})

target_link_libraries(${BINARY}_lib OpenGL::GL)
target_link_libraries(${BINARY}_lib glfw)
target_link_libraries(${BINARY}_run ${BINARY}_lib)
