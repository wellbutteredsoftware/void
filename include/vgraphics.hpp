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

    /// @brief Initalizes the `SDL_Window*` and `SDL_Renderer*` graphical backend.
    bool Init();

    /// 
    void BeginFrame();

    /// @brief Ends rendering and presents frame data to the display.
    void EndFrame();

    /// @brief Clears the current frame.
    /// @param r Red channel (range: 0.0 - 1.0)
    /// @param g Green channel (range: 0.0 - 1.0)
    /// @param b Blue channel (range: 0.0 - 1.0)
    /// @param a Alpha channel (range: 0.0 - 1.0)
    void Clear(float r, float g, float b, float a);

    /// @brief 
    /// @param texture 
    /// @param x 
    /// @param y 
    /// @param w 
    /// @param h 
    /// @param src_rec 
    void DrawTexture(SDL_Texture* texture, int x, int y, int w, int h, SDL_Rect* src_rec = (SDL_Rect*)nullptr);

    /// @brief Changes the title of the Window.
    /// @param title String ref to the new title
    void SetWindowTitle(const std::string& title);

    /// @brief Sets the fullscreen flag back and forth from `true` and `false`.
    /// @param fullscreen Boolean you want to pass to the `SDL_Window*`
    void SetFullscreen(bool fullscreen);

    /// @brief Resizes the window and renderer to the provided dimensions.
    /// @param new_width New width of the window in px
    /// @param new_height New height of the window in px
    void Resize(int new_width, int new_height);

    /// @brief 
    /// @return 
    SDL_Window* GetWindow() const { return window; }

    /// @brief 
    /// @return 
    SDL_Renderer* GetRenderer() const { return renderer; }

private:
    std::string window_title;
    int window_width;
    int window_height;
    bool is_fullscreen;
  
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool initalized = false;

    /// @brief Destroys data and frees memory related to `VGraphics`
    void Destroy();
};