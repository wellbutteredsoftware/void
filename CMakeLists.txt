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
    set(COMPILER_IS_GCC TRUE)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Clang detected...")
    set(COMPILER_IS_CLANG TRUE)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "MSVC detected...")
    set(COMPILER_IS_MSVC TRUE)
else()
    message(WARNING "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()
string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_UPPER)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(COMMON_OPT_FLAGS "")
set(COMMON_LINK_FLAGS "")

# Per-build-type compiler flags
if(BUILD_TYPE_UPPER STREQUAL "DEBUG")
    if(COMPILER_IS_GCC OR COMPILER_IS_CLANG)
        set(COMMON_OPT_FLAGS "-g -O0 -Wall -Wextra -Wpedantic")
        set(COMMON_LINK_FLAGS "")
    elseif(COMPILER_IS_MSVC)
        set(COMMON_OPT_FLAGS "/Zi /Od /W4")
        set(COMMON_LINK_FLAGS "/DEBUG")
    endif()
elseif(BUILD_TYPE_UPPER STREQUAL "RELEASE")
    if(COMPILER_IS_GCC OR COMPILER_IS_CLANG)
        set(COMMON_OPT_FLAGS "-O3 -DNDEBUG -ffast-math -flto")
        set(COMMON_LINK_FLAGS "-flto")
    elseif(COMPILER_IS_MSVC)
        set(COMMON_OPT_FLAGS "/O2 /DNDEBUG /GL")  # /GL = link-time optimization
        set(COMMON_LINK_FLAGS "/LTCG")            # LTCG = link-time code generation
    endif()
else()
    message(WARNING "Unknown build type: ${CMAKE_BUILD_TYPE}")
endif()

# Apply global flags
add_compile_options(${COMMON_OPT_FLAGS})
add_link_options(${COMMON_LINK_FLAGS})

string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_UPPER)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if(PURGE_DEPS)
    message(STATUS "Removing existing dependencies...")
    file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/external")
endif()

add_compile_options(${COMMON_OPT_FLAGS})
add_link_options(${COMMON_LINK_FLAGS})

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
file(GLOB ENGINE_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB ENGINE_INCLUDE CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/include/*.hpp")