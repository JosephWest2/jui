#include "line.hpp"

namespace ui {
namespace component {

void Line::Render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(renderer, points[0].x, points[0].y, points[1].x, points[1].y);
}

}  // namespace component
}  // namespace ui
