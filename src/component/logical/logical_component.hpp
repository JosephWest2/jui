#pragma once

#include <memory>
#include "component/component.hpp"
#include "window/renderer/renderer.hpp"
namespace component {
class Component;
namespace logical {

class LogicalComponent {
public:
    virtual void AfterDraw(window::renderer::Renderer& renderer) {}
    virtual void BeforeDraw(window::renderer::Renderer& renderer) {}
    virtual void AfterComponentRegister(std::shared_ptr<component::Component>& component) {}
    virtual ~LogicalComponent() = default;
};

}
}
