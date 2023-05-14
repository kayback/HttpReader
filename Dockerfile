FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive 

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y \
    build-essential \
    software-properties-common \
    wget \
    clang \
    cmake \
    python3 \
    python3-pip \
    git \
    lcov \
    && rm -rf /var/lib/apt/lists/*

RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - && add-apt-repository "deb http://apt.llvm.org/focal/ llvm-toolchain-focal-15 main"

RUN apt-get update && \
    apt-get install -y clang-15

RUN cd /usr/lib/llvm-15/bin && \
    for f in *; do rm -f /usr/bin/$f; \
        ln -s ../lib/llvm-15/bin/$f /usr/bin/$f; done

RUN pip3 install conan==1.60.0

WORKDIR /home/http_reader

CMD [ "/bin/bash" ]
