#pragma once
#include <memory>
#include <ranges>
#include <vector>

#include "component/logical/logical_component.hpp"

namespace component {
namespace logical {

class LogicContainer {
  public:
    virtual std::ranges::ref_view<std::vector<std::shared_ptr<LogicalComponent>,
                            std::allocator<std::shared_ptr<LogicalComponent>>>>
    LogicalComponents() = 0;
};

}  // namespace logical
}  // namespace component
