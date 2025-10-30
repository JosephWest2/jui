#include "component.hpp"

namespace component {
void Component::DrawRecursive(window::renderer::Renderer& renderer) {
    Draw(renderer);
    for (auto& component : children) {
        component->DrawRecursive(renderer);
    }
}
}  // namespace component
