# Void Engine

![Static Badge](https://img.shields.io/badge/Built_with-C++-blue?logo=cplusplus)
[![justforfunnoreally.dev badge](https://img.shields.io/badge/justforfunnoreally-dev-9ff)](https://justforfunnoreally.dev)

Void Engine is a game engine, built in C++ for beginner friendly, powerful game development. Void is an amalgam of projects and inspirations, coinciding into a singular, monolithic engine that can be built and used *nearly* everywhere.- 

Void is a passion project that has only a couple goals, to be an easy-to-use but powerful tool for gamedev, 

# Features

- 2D Rendering via SDL3
- WAV Audio processing with SDL_Audio

# Targets

By default, Void compiles down to shared objects--or libraries--to link to inside your own project. All you need to get started are the headers and the library. However, since you can also build a dynamic library, you can use a Foreign Function Interface (FFI) to use Void in a large amount of other programming languages. The choice between a static library and dynamic object can be made during configuration with the `-DBUILD_TYPE` flag in CMake.

Configuring this project is not easy, please refer to the [config guide](./CONFIGURING.md) provided in the root of the repo. This will provide an explanation and sample configurations that you can use.

> [!IMPORTANT]
> This section is unfinished and will be finished ASAP