#pragma once

#include "window/renderer/renderer.hpp"

using window::renderer::Renderer;

namespace component {


class Component {
public:
    virtual void Draw(Renderer& renderer) = 0;

    virtual ~Component() = default;

};

}
