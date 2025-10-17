#include "handler.hpp"
namespace input {

bool Handler::HandleInput(SDL_Event& e) {
    switch (e.type) {
        case SDL_EVENT_QUIT: {
            return true;
        }
        case SDL_EVENT_KEY_DOWN: {
            break;
        }
        case SDL_EVENT_KEY_UP: {
            break;
        }
        case SDL_EVENT_MOUSE_BUTTON_DOWN: {
            break;
        }
        case SDL_EVENT_MOUSE_BUTTON_UP: {
            break;
        }
        case SDL_EVENT_MOUSE_MOTION: {
            break;
        }
        case SDL_EVENT_WINDOW_RESIZED: {
            break;
        }
        case SDL_EVENT_WINDOW_MOVED: {
            break;
        }
        default: {
            break;
        }
    }
    return false;
}
}  // namespace input
