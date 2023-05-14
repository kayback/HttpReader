from conans import ConanFile, CMake

class HttpReaderConan(ConanFile):
    name = "HttpReader"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    requires = "libpcap/1.9.1", "gtest/1.10.0", "benchmark/1.5.6"
    generators = "cmake", "cmake_find_package"
    default_options = {"*:shared": True, "libpcap:shared": False}

    def configure(self):
        self.settings.compiler = "clang"
        self.settings.compiler.version = "15"
        self.settings.compiler.libcxx = "libstdc++11"
