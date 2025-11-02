#include "dynamic_text.hpp"
#include <cassert>
#include "SDL3_ttf/SDL_ttf.h"

namespace component {
namespace text {

void DynamicText::OnClick(math::geometry::Point point) { 
    button::Button::OnClick(point); 
    TTF_SubString substring;
    assert(TTF_GetTextSubStringForPoint(text, point.x, point.y, &substring));
    TTF_Font* font;
}

}  // namespace text
}  // namespace component
