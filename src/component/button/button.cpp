#include "button.hpp"
#include "input/button/button_input_manager.hpp"
namespace component {
namespace button {

Button::Button(std::shared_ptr<input::button::ButtonInputManager>& input_manager) {
    auto self = shared_from_this();
    input_manager->RegisterButton(self);
}

}
}

