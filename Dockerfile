# Ubuntu 20.04 LTS (Focal Fossa) tabanlı bir imaj kullanacağız
FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive 

# Paket listesini güncelleyelim ve gerekli araçları kuralım
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

# LLVM anahtarlarını ve deposunu ekleyelim
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - && add-apt-repository "deb http://apt.llvm.org/focal/ llvm-toolchain-focal-15 main"

# Clang ve LLVM'i kuralım
RUN apt-get update && \
    apt-get install -y clang-15

RUN cd /usr/lib/llvm-15/bin && \
    for f in *; do rm -f /usr/bin/$f; \
        ln -s ../lib/llvm-15/bin/$f /usr/bin/$f; done

# Conan'ı kurmak için pip3'ü kullanalım
RUN pip3 install conan==1.60.0

# Çalışma dizinini ayarlayalım
WORKDIR /http_reader

# Komut çizelgesini bash'e ayarlayalım
CMD [ "/bin/bash" ]
