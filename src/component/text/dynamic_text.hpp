#pragma once

#include "component/button/button.hpp"
#include "component/text/text.hpp"

namespace component {
namespace text {
enum class DynamicTextMode {
    Deselected,
    Editing
};
class DynamicText : public Text, public button::Button {
  protected:
    void OnClick(math::geometry::Point point) override;
  public:
    DynamicTextMode mode{DynamicTextMode::Deselected};
};
}  // namespace text
}  // namespace component
