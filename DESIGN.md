# Void Engine Design

## 0. Forward

This document serves as the formal technical specification and architectural reference for Void Engine. Unlike *public-facing* documentation, `[DESIGN.md](./DESIGN.md)` is intended for engine developers, project contributors and end users who require a comprehensive understanding of Void's internal structures. You're expected to know what you're doing. This assumes a strong knowledge of C and C++, low-level systems programming, as well as realtime application design and implementation. **This is not a resource for beginners.** 

The document is organized to reflect the major subsystems of the engine, with explicit detail about implementation patterns, external-facing C bindings, memory handling rules, lifecycle guarantees, and known tradeoffs. Remember, this project is licensed under [Apache-2.0](./LICENSE) and comes with **no warranty of any kind.**

## 1. Table of Contents

0. [Forward](#forward)
1. [Table of Contents](#table-of-contents)
2. [VGraphics and SDL3](#2-vgraphics-and-sdl3)

## 2. VGraphics and SDL3

`VGraphics` is the graphics subsystem. It abstracts SDL3's windowing and rendering interfaces for engine-managed and simplified rendering and viewport control.

Internally it wraps both an `SDL_Window*` and `SDL_Renderer*`, managing their lifecycle, framebuffer clearing, and common operations like rendering textures and window resizing.

VGraphics is not designed to be fully feature-complete in itself--it is a stable internal interface between SDL and the engine, with a fixed set of responsibilities and contracts:

### Responsibilities
- Initialize and destroy the SDL window and renderer
- Handle fullscreen toggling, resize events, and window title updates
- Provide `BeginFrame()` and `EndFrame()` methods for render loops
- Allow texture drawing via `DrawTexture()` with optional source cropping
- Support per-frame framebuffer clearing with RGBA float colors
- Expose access to `SDL_Window*` and `SDL_Renderer*` for low-level use

### Not Responsibilities
- Scene management or batching
- Resource caching
- Shader or post-processing support
- GPU pipeline abstraction (reserved for future backends)

### Construction

The `VGraphics` object must be created with a title, initial window dimensions, and an optional fullscreen toggle. By default the fullscreen flag is `false`.

```cpp
#include <vgraphics.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
    VGraphics gfx("Void Game", 640, 480, false);
    if (!gfx.Init()) {
        std:cerr << ":(" << std::endl;
        return -1;
    }

    return 0;
}
```

## 2.1. VGraphics::Init()

## 2.2. VGraphics::Destroy()

## 2.3. VGraphics::BeginFame()

## 2.4. VGraphics::EndFrame()

## 2.5. VGraphics::Clear()

## 2.6. VGraphics::DrawTexture()

## 2.7. VGraphics::SetWindowTitle()

## 2.8. VGraphics::SetFullscreen()

## 2.9. VGraphics::Resize

# Void Engine C APIs (for non C++ projects)