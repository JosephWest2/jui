#pragma once

#include "component.hpp"

namespace ui {
namespace component {
class Circle : public Component {
  private:
      SDL_Color fill_color{100, 100, 255, 255};
      SDL_Color border_color{255, 100, 255, 255};
  public:
    void Render(SDL_Renderer* renderer) override;
};
}  // namespace component
}  // namespace ui
