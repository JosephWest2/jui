#pragma once

#include "component/container/container.hpp"

namespace component {
namespace container {
    class Elipse : public Container {
        public:
        void Draw(SDL_Renderer* renderer) override {
            SDL_SetRenderDrawColor(renderer, fill_color.r, fill_color.g, fill_color.b, fill_color.a);
            SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g, border_color.b, border_color.a);
        }

    };

}  // namespace container
}  // namespace component
