FROM ubuntu:26.04

RUN apt update && apt install -y \
    g++ \
    cmake \
    libspdlog-dev \
    python3-dev \
    python3-numpy \
    python3-matplotlib

WORKDIR /app

COPY . .

RUN mkdir -p build && \
    mkdir -p pcm && \
    cd build && \
    cmake .. && \
    make

WORKDIR /app/build

CMD ["./tests"]