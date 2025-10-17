#pragma once

#include "SDL3/SDL_events.h"
namespace input {
class Handler {
  private:
  public:
    // returns if the application should quit
    bool HandleInput(SDL_Event& e);
};
}  // namespace input
