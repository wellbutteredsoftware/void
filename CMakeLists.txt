# Void Engine CMake Configuration
# (c) wellbutteredtoast 2025
#

cmake_minimum_required(VERSION 3.15)
project(void LANGUAGES CXX)

option(PURGE_DEPS "Delete existing built dependencies and force rebuild" OFF)
option(BUILD_SHARED_LIBS "Builds deps and engine as a shared library" ON)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/external/install")

# Setting C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setting default flags for each major compiler
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "GCC detected...")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Clang detected...")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "MSVC detected...")
else()
    message(WARNING "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

if(PURGE_DEPS)
    message(STATUS "Removing existing dependencies...")
    file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/external")
endif()

# The big section of checking deps and building them if they don't exist
# Some things are vendored and not checked for since they exist in the repo
# The actual process is handled by scripts, the sources are in the repo root!

message(STATUS "Collecting dependencies...")
if(WIN32)
    execute_process(
        # Probably not the best approach...
        COMMAND powershell -ExecutionPolicy Bypass -File "${CMAKE_SOURCE_DIR}/deps.ps1"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        RESULT_VARIABLE ps_res
    )

    if(NOT ps_res EQUAL 0)
        message(FATAL_ERROR "Dependency setup failed! (PowerShell)")
    endif()
else()
    execute_process(
        COMMAND bash "${CMAKE_SOURCE_DIR}/deps.sh"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        RESULT_VARIABLE sh_res
    )

    if(NOT sh_res EQUAL 0)
        message(FATAL_ERROR "Dependency setup failed! (Bash/Shell)")
    endif()
endif()

find_package(SDL3 REQUIRED)
find_package(SDL3_mixer REQUIRED)

# If we're here, then we can start grabbing actual engine files and start compiling!