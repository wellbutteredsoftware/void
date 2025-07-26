/**
 * include/vgraphics.hpp
 * 2025 (c) wellbutteredsoftware
 * Licensed under Apache-2.0
 * 
 * This handles both graphics backend and windowing.
 * The graphical backend of Void is SDL3, universal and functional. 
 */

#pragma once

#include <SDL3/SDL.h>
#include <string>

class VGraphics
{
public:
    VGraphics(const std::string& title, int width, int height, bool fullscreen = false);
    ~VGraphics();

    bool Init();
    void BeginFrame();
    void EndFrame();
    void Clear(float r, float g, float b, float a);

    // Helpful helper for drawing SDL textures to the display
    void DrawTexture(SDL_Texture* texture, int x, int y, int w, int h, SDL_Rect* src_rec = nullptr);

    void SetWindowTitle(const std::string& title);
    void SetFullscreen(bool fullscreen);
    void Resize(int new_width, int new_height);

    SDL_Window* GetWindow() const { return window; }
    SDL_Renderer* GetRenderer() const { return renderer; }

private:
    std::string window_title;
    int window_width;
    int window_height;
    bool is_fullscreen;
  
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool initalized = false;

    void Destroy();
};