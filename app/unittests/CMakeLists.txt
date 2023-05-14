file(GLOB TEST_SOURCES "*.cpp")

add_executable(tests ${TEST_SOURCES})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

find_package(GTest REQUIRED)

target_link_libraries(tests 
    GTest::gtest 
    GTest::gmock 
    GTest::gtest_main
    gcov
    HttpReaderLib  )

include(GoogleTest)
gtest_discover_tests(tests)