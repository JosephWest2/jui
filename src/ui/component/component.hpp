#pragma once

#include <memory>
#include <ranges>
#include <set>
#include <vector>

#include "SDL3/SDL_render.h"

using std::ranges::input_range;
using std::ranges::to;
using std::set;
using std::vector;
using std::unique_ptr;

namespace ui {
namespace component {

enum ChildProperties {

};

enum SelfProperties {

};

class Component {
  protected:
    set<ChildProperties> child_properties{};
    set<SelfProperties> self_properties{};
    vector<unique_ptr<Component>> children{};

  public:
    Component(input_range auto&& self_properties, input_range auto&& child_properties, input_range auto&& children)
        : child_properties(to<set<ChildProperties>>(child_properties)),
          self_properties(to<set<SelfProperties>>(self_properties)) {}
    virtual void Render(SDL_Renderer* renderer) = 0;

    virtual ~Component() = default;
};

}  // namespace component
}  // namespace ui
