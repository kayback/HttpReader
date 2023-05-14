cmake_minimum_required(VERSION 3.5)
project(HttpReader)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_subdirectory(app)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(HttpReaderLib PRIVATE -O3)
endif()
