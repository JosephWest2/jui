#include "rounded_rect.hpp"
#include "sdl3_gfx/SDL3_gfxPrimitives.h"
#include "window/renderer/renderer.hpp"

namespace component {
    namespace container {

    void RoundedRect::Draw(window::renderer::Renderer& renderer) {
        roundedBoxRGBA(renderer.renderer,
                       rect.x,
                       rect.y,
                       rect.w,
                       rect.h,
                       corner_arc_radius,
                       fill_color.r,
                       fill_color.g,
                       fill_color.b,
                       fill_color.a);
        roundedRectangleRGBA(renderer.renderer,
                             rect.x,
                             rect.y,
                             rect.w,
                             rect.h,
                             corner_arc_radius,
                             border_color.r,
                             border_color.g,
                             border_color.b,
                             border_color.a);
    }
    SDL_FRect RoundedRect::BoundingBox() { return rect; }
    SDL_FPoint RoundedRect::Position() { return {rect.x, rect.y}; }
    }  // namespace container
}
