#pragma once

#include <memory>
#include <set>
#include <vector>

#include "component/component_flags.hpp"
#include "component/logical/logical_component.hpp"
#include "window/renderer/renderer.hpp"

namespace window {
class Window;
}

namespace component {

namespace logical {
    class LogicalComponent;
}

class Component {
  protected:
    virtual void Draw(window::renderer::Renderer& renderer) = 0;

  public:
    std::set<ComponentFlags> component_flags;
    std::weak_ptr<window::Window> window;
    std::vector<std::shared_ptr<logical::LogicalComponent>> logical_components;
    bool ContainsComponent(std::shared_ptr<Component>& component) {
        for (auto& child : children) {
            if (child == component || child->ContainsComponent(component)) {
                return true;
            }
        }
        return false;
    }
    std::vector<std::shared_ptr<Component>> children;
    void DrawRecursive(window::renderer::Renderer& renderer);
    virtual ~Component() = default;
};

}  // namespace component
