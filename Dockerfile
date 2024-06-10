FROM emscripten/emsdk:3.1.61-arm64

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libasound2-dev \
    libegl1-mesa-dev \
    libgles2-mesa-dev \
    libglu1-mesa-dev \
    libx11-dev \
    libxcursor-dev \
    libxinerama-dev \
    libxrandr-dev \
    libxrender-dev \
    libxi-dev \
    pkg-config \
    xorg-dev

# Clone raylib
RUN git clone https://github.com/raysan5/raylib.git /opt/raylib

# Build for web
RUN cd /opt/raylib/src && \
    make EMSDK_PATH=/emsdk PLATFORM=PLATFORM_WEB -j4 && \
    make install PLATFORM=PLATFORM_WEB

# Mount the source code
VOLUME /src
WORKDIR /src

ENTRYPOINT [ "make PLATFORM=PLATFORM_WEB PROJECT_NAME=balloon-pop OBJS=*.cpp BUILD_MODE=RELEASE RAYLIB_PATH=/opt/raylib PRELOAD_FILE=./assets/ -B -e" ]