#pragma once

#include <set>

#include "component/component.hpp"
#include "component/component_flags.hpp"
namespace component {
namespace container {
class Container : public Component {
  public:
      SDL_Color fill_color;
      SDL_Color border_color;
    std::set<ComponentFlags> container_flags;
};

}  // namespace container
}  // namespace component
