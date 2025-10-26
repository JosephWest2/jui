#pragma once
#include <memory>
#include <ranges>
#include <vector>

#include "component/logical/logical_component.hpp"

using std::allocator;
using std::shared_ptr;
using std::vector;
using std::ranges::ref_view;

namespace component {
namespace logical {

class LogicContainer {
  public:
    virtual ref_view<vector<shared_ptr<LogicalComponent>,
                            allocator<shared_ptr<LogicalComponent>>>>
    LogicalComponents() = 0;
};

}  // namespace logical
}  // namespace component
