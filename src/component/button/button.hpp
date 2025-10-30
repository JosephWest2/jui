#pragma once

#include <functional>
#include <memory>
#include "component/component.hpp"
#include "math/geometry/geometry.hpp"
namespace input {
namespace button {
class ButtonInputManager;
}
}
namespace component {
namespace button {

class Button : public Component, public std::enable_shared_from_this<Button> {
    public:
        // function that takes the click point as an argument
        std::function<void(math::geometry::Point)> on_click;

        Button(std::shared_ptr<input::button::ButtonInputManager>& input_manager);
};


} // namespace button
} // namespace component
