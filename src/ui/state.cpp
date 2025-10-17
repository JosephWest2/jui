#include "state.hpp"
namespace ui {

void State::Add(std::unique_ptr<ui::component::Component>&& component) {
    components.push_back(std::move(component));
}
void State::Render(SDL_Renderer* renderer) {
    for (auto& component : components) {
        component->Render(renderer);
    }
}

}  // namespace ui
