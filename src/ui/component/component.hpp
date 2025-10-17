#pragma once

#include <memory>
#include <ranges>
#include <set>
#include <vector>

#include "SDL3/SDL_render.h"

namespace ui {
namespace component {

enum ChildProperties {

};

enum SelfProperties {

};

class Component {
  protected:
    std::set<ChildProperties> child_properties{};
    std::set<SelfProperties> self_properties{};
    std::vector<std::unique_ptr<Component>> children{};

  public:
    template <std::ranges::input_range R1,
              std::ranges::input_range R2,
              std::ranges::input_range R3>
    Component(R1&& self_properties, R2&& child_properties, R3&& children)
        : child_properties(std::ranges::begin(child_properties),
                           std::ranges::end(child_properties)),
          self_properties(std::ranges::begin(self_properties),
                          std::ranges::end(self_properties)) {}
    virtual void Render(SDL_Renderer* renderer) = 0;

    virtual ~Component() = default;
};

}  // namespace component
}  // namespace ui
