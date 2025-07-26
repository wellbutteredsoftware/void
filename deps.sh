#!/bin/bash

# Dependency setup script for Void
# Do not edit, or run. This'll run
# automatically with CMake config.

set -eu

if ! command git -v >/dev/null 2>&1; then
    echo "Fatal: git is missing!" >&2
    exit 1
fi

if ! command make --version >/dev/null 2>&1; then
    echo "Fatal: make is missing!" >&2
    exit 1
fi

if ! command ninja --version >/dev/null 2>&1; then
    echo "Fatal: ninja is missing!" >&2
    exit 1
fi

if [ ! -d external ]; then
    mkdir -p external
fi

if [ ! -d external/sdl3 ]; then
    git clone --branch release-3.2.x https://github.com/libsdl-org/SDL --depth 1 external/sdl3
    cd external/sdl3
    cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_INSTALL_PREFIX=../install

    cmake --build build -- -j"$(nproc)"
    cmake --install build 
    cd ../..
fi

# Don't edit this branch for sdl3_mixer at this time!
# Every other branch seems to break stuff
if [ ! -d external/sdl3_mixer ]; then
    git clone --branch sdl2-api-on-sdl3 https://github.com/libsdl-org/SDL_mixer --depth 1 external/sdl3_mixer
    cd external/sdl3_mixer

    cmake -S . -B build -G Ninja \
        -DCMAKE_PREFIX_PATH="$(realpath ../install)" \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_SHARED_LIBS=OFF \
        -DSDL_mixer_TESTS=OFF \
        -DSDL_mixer_SDL2_REQUIRED=OFF \
        -DSDL_mixer_SDL3_REQUIRED=ON \
        -DCMAKE_INSTALL_PREFIX=../install

    cmake --build build -- -j"$(nproc)"
    cmake --install build
    cd ../..
fi

if [ ! -d external/install/stb ]; then
    mkdir -p external/install/stb
    curl -Lo external/install/stb/stb_vorbis.c https://raw.githubusercontent.com/nothings/stb/refs/heads/master/stb_vorbis.c
fi

echo "Dependencies built!"
exit 0
