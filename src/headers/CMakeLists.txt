set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.h *.cpp *.c)

target_link_libraries(${BINARY}_lib ${SOURCES})
