cmake_minimum_required(VERSION 3.5)
project(MyProject)

# set(CMAKE_CC_COMPILER clang)
# set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# 'app' klasöründeki CMake dosyasını ekleyin
add_subdirectory(app)

# Derleme türüne göre optimize edin
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(my_app PRIVATE -O3)
endif()
