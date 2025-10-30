#pragma once

#include <set>

#include "component/component.hpp"
#include "component/component_flags.hpp"
namespace component {
namespace container {
class Container : public Component {
  public:
    std::set<ComponentFlags> container_flags;
};

}  // namespace container
}  // namespace component
