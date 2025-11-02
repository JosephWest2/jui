#include "ellipse.hpp"

#include <cassert>

#include "sdl3_gfx/SDL3_gfxPrimitives.h"
#include "window/renderer/renderer.hpp"

namespace component {
namespace container {

void Ellipse::Draw(window::renderer::Renderer& renderer) {
    assert(filledEllipseRGBA(renderer.renderer,
                             center_position.x,
                             center_position.y,
                             radius_x,
                             radius_y,
                             fill_color.r,
                             fill_color.g,
                             fill_color.b,
                             fill_color.a));
    assert(ellipseRGBA(renderer.renderer,
                       center_position.x,
                       center_position.y,
                       radius_x,
                       radius_y,
                       border_color.r,
                       border_color.g,
                       border_color.b,
                       border_color.a));
}
}  // namespace container
}  // namespace component
