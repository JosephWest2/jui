#include "rect.hpp"

namespace ui {
namespace component {

void Rect::Render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, fill_color.r, fill_color.g, fill_color.b, fill_color.a);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g, border_color.b, border_color.a);
    SDL_RenderRect(renderer, &rect);
}

}  // namespace component
}  // namespace ui
