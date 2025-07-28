#include "vgraphics.hpp"
#include <SDL3/SDL.h>
#include <iostream>

VGraphics::VGraphics(const std::string& title, int width, int height, bool fullscreen)
    : window_title(title), window_width(width), window_height(height), is_fullscreen(fullscreen) {}

VGraphics::~VGraphics() {
    Destroy();  
}

bool VGraphics::Init() {
    if (initalized) return true;
    initalized = false;

    Uint32 window_flags = SDL_WINDOW_RESIZABLE;
    if (is_fullscreen)
        window_flags |= SDL_WINDOW_FULLSCREEN;

    if (SDL_CreateWindowAndRenderer(window_title.c_str(), window_width, window_height,
        window_flags, &window, &renderer) != 0)
    {
        std::cerr << "SDL_CreateWindowAndRenderer() failed: " << SDL_GetError() << "\n";
        return initalized;
    }

    initalized = true;
    return initalized;
}

void VGraphics::BeginFrame() {
    // No-op for now...
}

void VGraphics::EndFrame() {
    SDL_RenderPresent(renderer);
}

void VGraphics::Clear(float r, float g, float b, float a) {
    SDL_SetRenderDrawColor(renderer,
                           static_cast<Uint8>(r * 255),
                           static_cast<Uint8>(g * 255),
                           static_cast<Uint8>(b * 255),
                           static_cast<Uint8>(a * 255));
    SDL_RenderClear(renderer);
}

void VGraphics::SetWindowTitle(const std::string& title) {
    window_title = title;
    if (window)
        SDL_SetWindowTitle(window, title.c_str());
}

void VGraphics::SetFullscreen(bool fullscreen) {
    is_fullscreen = fullscreen;
    if (window) {
        SDL_SetWindowFullscreen(window, fullscreen ? true : false);
    }
}

void VGraphics::Resize(int new_width, int new_height) {
    window_width = new_width;
    window_height = new_height;
    if (window) {
        SDL_SetWindowSize(window, new_width, new_height);
    }
}

void VGraphics::Destroy() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    initalized = false;
}