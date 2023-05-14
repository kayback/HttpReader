# HTTP Reader

This application captures packets from a network interface or a pcap file, extracts the User-Agent information in HTTP packets, and calculates the bandwidth of this User-Agent.

The application is compiled and used within a Docker Container. Docker Engine must be installed on your computer for installation.

The following commands are written assuming that you are in the main directory of the project. If you want to operate from a different directory, paths can be changed as needed.

First, the Docker image needs to be built with the command below. Here, the "--network=host" parameter is used for the container to access the host computer's traffic. Optionally, a different network can be defined like a bridge or you can create your own network profile and set it up in this way. If this parameter is not specified, it is set to bridge by default.

## Docker build:
    docker build --network=host -t httpreaderimage .

After building the image, a container needs to be created and run with the command below. Here, the directory to be mounted to the container is specified with the "-v" parameter.

## Docker run:
    docker run -v $(pwd):/home/http_reader -p 8080:80 --name httpreader -it httpreaderimage

When the container is up and running, you can proceed to the steps necessary to compile the application.
Conan is a package manager tool that typically manages dependencies for c++ projects. Conan has its own repository containing dependencies, but you can also create your own repository and get packages from your own repo. The conan install command below is used to obtain the necessary third-party dependencies for the application. Here, since there is no need for a private conan repo, packages are taken from the official conan repo.

The "--profile" parameter is given for Conan to work with our own created profile. If this parameter is not given, Conan works with the default profile. The default profile is set to compile packages with gcc, but since the clang 15.0.0 compiler is preferred to compile the application, there was a need to create a custom profile. The "--build missing" parameter is used to compile missing packages while pulling packages. If there is a package that has been previously pulled and compiled, it will not compile again. "-if ./build" is specified to extract files like conanbuildinfo.cmake created by Conan into a folder named build.

## Conan command:
    conan install --profile ./conan_clang_profile --build missing -if ./build .

After dependencies are installed with Conan, the application can be compiled with the cmake commands below. Compilation commands are divided into Debug and Release. Debug compilation is the version suitable for working during the development process. The Release version is optimized compiled and becomes suitable for running benchmark tests.

## Debug build:
### Configure command:
    cmake -DCMAKE_BUILD_TYPE=Debug -DTEST_BUILD=ON -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang-15 -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++-15 -B/home/http_reader/build -G "Unix Makefiles" .
### Build command:
    cmake --build /home/http_reader/build --config Debug --target all -j 10 

## Release build:
### Configure command:
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang-15 -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++-15 -B/home/http_reader/build -G "Unix Makefiles" .
### Build command:
    cmake --build /home/http_reader/build --config Release --target all -j 10

After the application is compiled, the executable files will be created under the build/bin directory. The application can be used in the following ways:

## Running the application:
    ./HttpReader    --> Analyzes HTTP requests passing through the "eth0" interface. Does not print results.
    ./HttpReader --pcap test.pcap   --> Analyzes HTTP requests in the specified pcap file. Does not print results.

    ./HttpReader --print    --> Analyzes HTTP requests passing through the "eth0" interface. Prints results in intervals of 1 second.
    ./HttpReader --print --pcap test.pcap   --> Analyzes HTTP requests in the specified pcap file. Prints results in intervals of 1 second.

### Unit-test and benchmark:
    ./tests     --> Runs the unit-tests.
    ./benchmark     --> Runs the benchmark tests.

