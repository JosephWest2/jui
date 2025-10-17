#pragma once

#include "component.hpp"

namespace ui {
namespace component {
class Line : public Component {
  private:
      SDL_Color color{0, 255, 255, 255};
      SDL_FPoint points[2]{{0, 0}, {100, 100}};
  public:
    void Render(SDL_Renderer* renderer) override;
};
}  // namespace component
}  // namespace ui
