#pragma once

#include <memory>
#include <vector>

namespace component {
namespace button {
class Button;
}
}  // namespace component
namespace input {
namespace button {

class ButtonInputManager {
  private:
    std::vector<std::weak_ptr<component::button::Button>> buttons;

  public:
    void RegisterButton(std::shared_ptr<component::button::Button>& button);
};

}  // namespace button
}  // namespace input
