#include "renderer.hpp"

#include <cassert>
#include <stdexcept>

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

using std::runtime_error;
using std::string;

namespace window {
namespace renderer {

Renderer::Renderer(SDL_Window* sdl_window) {
    assert(sdl_window);
    renderer = SDL_CreateRenderer(sdl_window, SDL_GetWindowTitle(sdl_window));
    if (!renderer) {
        throw runtime_error("Failed to create SDL renderer: " + string(SDL_GetError()));
    }
    text_engine = TTF_CreateRendererTextEngine(renderer);
    if (!text_engine) {
        throw runtime_error("Failed to create SDL text engine: " + string(SDL_GetError()));
    }
}

}  // namespace renderer
}  // namespace window
