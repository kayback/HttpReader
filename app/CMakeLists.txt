file(GLOB SOURCES "src/*.cpp")

include_directories(include)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_library(HttpReaderLib ${SOURCES})

add_executable(HttpReader ${SOURCES})
target_link_libraries(HttpReader CONAN_PKG::libpcap)

target_link_libraries(HttpReaderLib CONAN_PKG::libpcap)

add_subdirectory(unittests)
add_subdirectory(benchmark)