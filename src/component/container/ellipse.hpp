#pragma once

#include "component/container/container.hpp"

namespace component {
namespace container {
class Ellipse : public Container {
  public:
    SDL_FPoint center_position;
    float radius_x;
    float radius_y;
    void Draw(window::renderer::Renderer& renderer) override;
    SDL_FRect BoundingBox() override {
        return {center_position.x - radius_x, center_position.y - radius_y, radius_x * 2, radius_y * 2};
    }
    SDL_FPoint Position() override {
        return {center_position.x - radius_x, center_position.y - radius_y};
    }
};

}  // namespace container
}  // namespace component
