set(BINARY ${CMAKE_PROJECT_NAME}_test)

include(ExternalProject)

set(GTEST_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/lib/googletest" CACHE PATH "Installation directory for Google Test")

ExternalProject_Add(
    googletest
    PREFIX "${CMAKE_BINARY_DIR}/googletest"
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${GTEST_INSTALL_PREFIX}
)

add_library(gtest INTERFACE IMPORTED GLOBAL)
add_dependencies(gtest googletest)

target_include_directories(gtest INTERFACE ${GTEST_INSTALL_PREFIX}/include)
target_link_libraries(gtest INTERFACE ${GTEST_INSTALL_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX})

add_library(gtest_main INTERFACE IMPORTED GLOBAL)
add_dependencies(gtest_main googletest)
target_link_libraries(gtest_main INTERFACE ${GTEST_INSTALL_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})

file(GLOB TEST_SOURCES  *.cpp)

add_executable(${BINARY} ${TEST_SOURCES})

set_property(TARGET ${BINARY} PROPERTY CXX_STANDARD 17)

enable_testing()

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} gtest)

target_link_libraries(${BINARY} ${CMAKE_PROJECT_NAME}_lib)
