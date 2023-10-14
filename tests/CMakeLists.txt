set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB TEST_SOURCES  *.cpp)

add_executable(${BINARY} ${TEST_SOURCES})

set_property(TARGET ${BINARY} PROPERTY CXX_STANDARD 17)

enable_testing()

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} gtest)

target_link_libraries(${BINARY} ${CMAKE_PROJECT_NAME}_lib)
