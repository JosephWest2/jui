#pragma once

#include "SDL3/SDL_events.h"
namespace input {
class InputHandler {
  private:
  public:
    void HandleKeyDown(SDL_KeyboardEvent& e);
    void HandleKeyUp(SDL_KeyboardEvent& e);
    void HandleMouseMotion(SDL_MouseMotionEvent& e);
    void HandleMouseDown(SDL_MouseButtonEvent& e);
    void HandleMouseUp(SDL_MouseButtonEvent& e);
    void HandleMouseWheel(SDL_MouseWheelEvent& e);
};
}  // namespace input
