# Dependency setup script for Void (PowerShell)
# Do not edit or run manually. This is called by the CMake config.

$ErrorActionPreference = "Stop"

function Check-Command($command, $errorMessage) {
    if (-not (Get-Command $command -ErrorAction SilentlyContinue)) {
        Write-Error $errorMessage
        exit 1
    }
}

Check-Command git "Fatal: git is missing!"
Check-Command make "Fatal: make is missing!"
Check-Command ninja "Fatal: ninja is missing!"

# Create external folder if missing
if (-not (Test-Path -Path "external" -PathType Container)) {
    New-Item -Path "external" -ItemType Directory | Out-Null
}

# SDL3
if (-not (Test-Path -Path "external/sdl3" -PathType Container)) {
    git clone --branch release-3.2.x https://github.com/libsdl-org/SDL --depth 1 external/sdl3

    Push-Location external/sdl3
    cmake -S . -B build -G Ninja `
        -DCMAKE_BUILD_TYPE=Release `
        -DBUILD_SHARED_LIBS=OFF `
        -DCMAKE_INSTALL_PREFIX=../install

    cmake --build build -- -j $(Get-ProcessorCount)
    cmake --install build
    Pop-Location
}

# SDL3_mixer - must use the sdl2-api-on-sdl3 branch!
if (-not (Test-Path -Path "external/sdl3_mixer" -PathType Container)) {
    git clone --branch sdl2-api-on-sdl3 https://github.com/libsdl-org/SDL_mixer --depth 1 external/sdl3_mixer

    Push-Location external/sdl3_mixer
    $prefixPath = Resolve-Path ../install
    cmake -S . -B build -G Ninja `
        -DCMAKE_PREFIX_PATH="$prefixPath" `
        -DCMAKE_BUILD_TYPE=Release `
        -DBUILD_SHARED_LIBS=OFF `
        -DSDL_mixer_TESTS=OFF `
        -DSDL_mixer_SDL2_REQUIRED=OFF `
        -DSDL_mixer_SDL3_REQUIRED=ON

    cmake --build build -- -j $(Get-ProcessorCount)
    cmake --install build
    Pop-Location
}

Write-Host "Dependencies built!"
exit 0
