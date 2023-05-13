# file(GLOB TEST_SOURCES "*.cpp")

# add_executable(tests ${TEST_SOURCES})

# list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
# list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

# find_package(GTest REQUIRED)



# target_link_libraries(tests 
#     GTest::gtest 
#     GTest::gmock 
#     GTest::gtest_main
#     gcov
#     my_app  )

# include(GoogleTest)
# gtest_discover_tests(tests)

# # if(CMAKE_BUILD_TYPE STREQUAL "Debug")
# #     target_compile_options(my_app PRIVATE --coverage)
# #     target_link_options(my_app PRIVATE --coverage)

# #     add_custom_target(coverage
# #         COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/coverage
# #         COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/coverage
# #             lcov --capture --directory ../app --output-file coverage.info
# #         COMMAND lcov --remove coverage.info '/usr/*' '*/gtest/*' '*/gmock/*' --output-file coverage.info.cleaned
# #         COMMAND ${CMAKE_COMMAND} -E rename coverage.info.cleaned coverage.info
# #         COMMAND genhtml coverage.info
# #         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
# #         COMMENT "Collecting code coverage and generating HTML report..."
# #     )
# # endif()