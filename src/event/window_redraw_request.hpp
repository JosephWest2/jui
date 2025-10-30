#pragma once

#include "SDL3/SDL_video.h"
#include "event/event.hpp"

namespace event {

class WindowRedrawRequest : public Event {
public:
    SDL_WindowID window_id;
};

}
