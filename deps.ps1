# Dependency setup script for Void (PowerShell)
# Do not edit or run manually. This is called by the CMake config.

$ErrorActionPreference = "Stop"
$jobs = [Environment]::ProcessorCount

function Check-Command($command, $errorMessage) {
    if (-not (Get-Command $command -ErrorAction SilentlyContinue)) {
        Write-Error $errorMessage
        exit 1
    }
}

Check-Command git "Fatal: git is missing!"
Check-Command ninja "Fatal: ninja is missing!"

# Create external folder if missing
if (-not (Test-Path -Path "external" -PathType Container)) {
    New-Item -Path "external" -ItemType Directory | Out-Null
}

# SDL3
if (-not (Test-Path -Path "external/sdl3" -PathType Container)) {
    git clone --branch release-3.2.x https://github.com/libsdl-org/SDL --depth 1 external/sdl3

    Push-Location external/sdl3

    if (-not (Test-Path -Path "../install" -PathType Container)) {
        New-Item -Path "../install" -ItemType Directory | Out-Null
    }

    $installPath = (Resolve-Path ../install).Path

    cmake -S . -B build -G Ninja `
        -DCMAKE_BUILD_TYPE=Release `
        -DBUILD_SHARED_LIBS=OFF `
        -DCMAKE_INSTALL_PREFIX="$installPath"

    cmake --build build -- -j $jobs
    cmake --install build
    Pop-Location
}

# SDL3_mixer - must use the sdl2-api-on-sdl3 branch!
if (-not (Test-Path -Path "external/sdl3_mixer" -PathType Container)) {
    git clone --branch sdl2-api-on-sdl3 https://github.com/libsdl-org/SDL_mixer --depth 1 external/sdl3_mixer

    Push-Location external/sdl3_mixer
    $prefixPath = (Resolve-Path ../install).Path

    cmake -S . -B build -G Ninja `
        -DCMAKE_PREFIX_PATH="$prefixPath" `
        -DCMAKE_BUILD_TYPE=Release `
        -DBUILD_SHARED_LIBS=OFF `
        -DSDL_mixer_TESTS=OFF `
        -DSDL_mixer_SDL2_REQUIRED=OFF `
        -DSDL_mixer_SDL3_REQUIRED=ON `
        -DSDLMIXER_VENDORED=OFF `
        -DCMAKE_INSTALL_PREFIX="../install"

    cmake --build build -- -j $jobs
    cmake --install build
    Pop-Location
}

$stbPath = "external/install/stb/stb_vorbis.c"
if (-not (Test-Path -Path $stbPath)) {
    if (-not (Test-Path -Path "external/install/stb" -PathType Container)) {
        New-Item -Path "external/install/stb" -ItemType Directory | Out-Null
    }

    Invoke-WebRequest -Uri "https://raw.githubusercontent.com/nothings/stb/refs/heads/master/stb_vorbis.c" `
                      -OutFile $stbPath
}

Write-Host "Dependencies built!"
exit 0
