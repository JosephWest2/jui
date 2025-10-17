#pragma once
#include <memory>
#include <vector>

#include "component/component.hpp"

namespace ui {

class State {
  private:
    std::vector<std::unique_ptr<ui::component::Component>> components{};
    bool has_changed = false;

  public:
    void Add(std::unique_ptr<ui::component::Component>&& component);
    bool HasChanged() { return has_changed; }
    void Render(SDL_Renderer* renderer);
};

}  // namespace ui
