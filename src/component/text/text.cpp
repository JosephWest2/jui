#include "text.hpp"
#include <cassert>

namespace component {
namespace text {

void Text::Draw(window::renderer::Renderer& renderer) {}

SDL_FRect Text::BoundingBox() { 
    int w, h;
    assert(TTF_GetTextSize(text, &w, &h));
    SDL_FPoint position = Position();
    return {position.x, position.y, (float)w, (float)h}; 
}

SDL_FPoint Text::Position() { 
    int x, y;
    assert(TTF_GetTextPosition(text, &x, &y));
    return {(float)x, (float)y}; 
}

}  // namespace text
}  // namespace component
