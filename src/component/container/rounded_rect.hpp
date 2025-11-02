#pragma once

#include "component/container/container.hpp"

namespace component {
    namespace container {
        class RoundedRect: public Container {
            public:
                SDL_FRect rect;
                float corner_arc_radius;
                void Draw(window::renderer::Renderer& renderer) override;
                SDL_FRect BoundingBox() override;
                SDL_FPoint Position() override;
        };
    }
    
}
