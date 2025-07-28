# Void Config Guide

Void supports a wide range of configuration options, and its build system is based on **CMake**. [**CMake**](https://cmake.org/) is a cross-platform build system, primarily used for C and C++ projects. This engine provides numerous configuration flags you should be aware of when building it yourself. This guide assumes you're already familiar with the basics of CMake.

CMake handles most of the heavy lifting, including fetching and building dependencies from GitHub. However, it expects standard build tools like `make` to be available on your system. These tools are usually preinstalled on most Unix-like operating systems.

If you're on Windows, you’ll need to install a compatible toolchain. The recommended option is [MinGW-w64](https://www.mingw-w64.org/), which provides a full GCC-based environment for Windows. Follow the link provided for download and installation instructions.

## Sample Configurations

If you just want to grab a command that matches what you're looking for and run with it, this is the place to be. These sample commands will get you up and running quickly.

```sh
# Universal default configuration (debug)
cmake -S . -B build -G <generator>
```

```sh
# Default config in Release mode
cmake -S . -B build -G <generator> -DCMAKE_BUILD_TYPE=Release
```

```sh
# CMake using your own compilers
cmake -S . -B build -G <generator> -DCMAKE_C_COMPILER=<path/to/c> -DCMAKE_CXX_COMPILER=<path/to/cpp>
```

```sh
# Removing all deps and rebuilding them
cmake -S . -B build -G <generator> -DPURGE_DEPS=ON
```

<!-- I'm not 100% sure how cross compiling will work here so I'll avoid it for now -->  

# List of Switches

This is the list of every single switch and flag you can pass into CMake for this project, some CMake builtin flags are here but not *everything.*

| Flag | Description |
| ---- | ----------- |
| `-S` | Specifies the source of the `CMakeLists.txt` file. |
| `-B` | Specifies where to build the program and generator files. |
| `-G` | Specify the generator. (ie. Ninja, Make, NMake, Visual Studio, etc.) |
| `-DCMAKE_BUILD_TYPE` | Build type, the default is Debug.
| `-DCMAKE_C_COMPILER` | Specify the C compiler you'd like to use. |
| `-DCMAKE_CXX_COMPILER` | Specify the C++ compiler you'd like to use. |
| `-DBUILD_SHARED_LIBS` | Specify if the engine will be built as a static or dynamic library. |
| `-DPURGE_DEPS` | Deletes and recompiles **every** dependency for Void. |
| `-DPEDANTIC_COMPILING` | Enables highest warning levels on selected compiler. |
| `-DWARNINGS_ARE_ERRORS` | Every warning is an error and will stop compilation. |