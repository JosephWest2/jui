#include "button_input_manager.hpp"
namespace input {
namespace button {

void ButtonInputManager::RegisterButton(std::shared_ptr<component::button::Button>& button) {
    buttons.push_back(button);
}

}  // namespace button
}  // namespace input
