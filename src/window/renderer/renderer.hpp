#pragma once

#include "SDL3/SDL_render.h"
#include "SDL3_ttf/SDL_ttf.h"

namespace window {
namespace renderer {

class Renderer {
  protected:
    SDL_Renderer* renderer{nullptr};
    TTF_TextEngine* text_engine{nullptr};

  public:
    Renderer(SDL_Window* sdl_window);
    ~Renderer();
};

}  // namespace renderer
}  // namespace window
