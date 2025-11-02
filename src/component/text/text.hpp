#pragma once


#include "SDL3_ttf/SDL_ttf.h"
#include "component/component.hpp"

namespace component {
namespace text {
class Text : public Component {
  public:
    TTF_Text* text;
    void Draw(window::renderer::Renderer& renderer) override;
    SDL_FRect BoundingBox() override;
    SDL_FPoint Position() override;
};
}  // namespace text
}  // namespace component
