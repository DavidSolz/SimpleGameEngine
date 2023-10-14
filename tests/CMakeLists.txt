set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB TEST_SOURCES  *.cpp)

add_executable(${BINARY} ${TEST_SOURCES})

enable_testing()

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} gtest)

target_link_libraries(${BINARY} ${CMAKE_PROJECT_NAME}_lib)