file(GLOB SOURCES "src/*.cpp") # 'src' klasöründeki tüm .cpp dosyalarını bulun

include_directories(include) # 'include' klasörünü dahil edin

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_library(my_app ${SOURCES}) # Uygulamanızı oluşturan kaynak dosyalarını ekleyin

add_executable(my_apps ${SOURCES})
target_link_libraries(my_apps CONAN_PKG::libpcap)

target_link_libraries(my_app CONAN_PKG::libpcap) # my_app hedefini libpcap kütüphanesine bağlayın

add_subdirectory(unittests)
add_subdirectory(benchmark)