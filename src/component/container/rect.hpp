#pragma once

#include "SDL3/SDL_render.h"
#include "component/container/container.hpp"

namespace component {
namespace container {
class Rect : public Container {
public:
    SDL_FRect rect;
    void Draw(SDL_Renderer* renderer) override {
        SDL_SetRenderDrawColor(renderer, fill_color.r, fill_color.g, fill_color.b, fill_color.a);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g, border_color.b, border_color.a);
        SDL_RenderRect(renderer, &rect);
    }
    SDL_FRect BoundingBox() override {
        return rect;
    }
    SDL_FPoint Position() override {
        return {rect.x, rect.y};
    }

};
}  // namespace container
}  // namespace component
