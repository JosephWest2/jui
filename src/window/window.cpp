#include "window.hpp"

#include <stdexcept>

#include "SDL3/SDL_video.h"

using std::runtime_error;
using std::string;

namespace window {

Window::Window(const char* window_title, int width, int height, ControlFlow control_flow) : control_flow(control_flow) {
    window = SDL_CreateWindow(window_title, width, height, SDL_WINDOW_RESIZABLE);
    if (!window) {
        throw runtime_error("Failed to create SDL window: " + string(SDL_GetError()));
    }
    renderer = Renderer(window);
}

const char* Window::Title() const { return SDL_GetWindowTitle(window); }

pair<int, int> Window::GetDimensions() const {
    int w, h;
    if (!SDL_GetWindowSize(window, &w, &h)) {
        throw runtime_error("Failed to get window size: " + string(SDL_GetError()));
    }
    return {w, h};
}

void Window::Draw() {
    assert(renderer);
    for (auto& component : components) {
        component.Draw(*renderer);
    }
}

int Window::GetWidth() const { return GetDimensions().first; }
int Window::GetHeight() const { return GetDimensions().second; }
Window::~Window() { SDL_DestroyWindow(window); };

}  // namespace window
