#pragma once

#include "component.hpp"

namespace ui {
namespace component {
namespace rect {

enum class SelfProperties {

};

enum class ChildProperties {
    STRETCH_TO_FILL = 0,
};

class Rect : public Component {
  protected:
    std::set<ChildProperties> rect_child_properties{};
    std::set<SelfProperties> rect_self_properties{};
    SDL_Color fill_color{0, 0, 255, 255};
    SDL_Color border_color{0, 150, 100, 255};
    SDL_FRect rect{0, 0, 100, 100};

  public:
    template <std::ranges::input_range R1,
              std::ranges::input_range R2,
              std::ranges::input_range R3,
              std::ranges::input_range R4,
              std::ranges::input_range R5>
    Rect(R1&& child_properties,
         R2&& self_properties,
         R3&& children,
         R4&& rect_child_properties,
         R5&& rect_self_properties,
         SDL_FRect rect,
         SDL_Color fill_color,
         SDL_Color border_color)
        : component::Component(self_properties, child_properties),
          rect_child_properties(std::ranges::begin(rect_child_properties),
                                std::ranges::end(rect_child_properties)),
          rect_self_properties(std::ranges::begin(rect_self_properties),
                               std::ranges::end(rect_self_properties)),
          fill_color(fill_color),
          border_color(border_color),
          rect(rect) {}

    void Render(SDL_Renderer* renderer) override;
};

}  // namespace rect
}  // namespace component
}  // namespace ui
