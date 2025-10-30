#include "window.hpp"

#include <stdexcept>

#include "SDL3/SDL_video.h"

namespace window {

Window::Window(const char* window_title, int width, int height, ControlFlow control_flow) : control_flow(control_flow) {
    window = SDL_CreateWindow(window_title, width, height, SDL_WINDOW_RESIZABLE);
    if (!window) {
        throw std::runtime_error("Failed to create SDL window: " + std::string(SDL_GetError()));
    }
    renderer = renderer::Renderer(window);
}

std::pair<int, int> Window::GetDimensions() const {
    int w, h;
    if (!SDL_GetWindowSize(window, &w, &h)) {
        throw std::runtime_error("Failed to get window size: " + std::string(SDL_GetError()));
    }
    return {w, h};
}

void Window::Draw() {
    assert(renderer);
    for (auto& component : components) {
        component->DrawRecursive(*renderer);
    }
}

Window::~Window() { SDL_DestroyWindow(window); };

void Window::DrawIfNeeded() {
    if (window_redraw_needed) {
        Draw();
        window_redraw_needed = false;
    }
}
void Window::RegisterComponent(std::shared_ptr<component::Component>& component) { 
    component->window = shared_from_this();
    components.push_back(component);
}
bool Window::ContainsComponent(std::shared_ptr<component::Component>& component) {
    for (auto& c : components) {
        if (c == component || c->ContainsComponent(component)) {
            return true;
        }
    }
    return false;
}
}  // namespace window
