#pragma once

#include <cstdint>
#include <memory>
#include <queue>
#include <variant>

#include "SDL3/SDL_events.h"
#include "event/event.hpp"

namespace event {

class EventManager {
  private:
    uint32_t custom_event_id;
    EventManager();
    ~EventManager() = default;

  public:
    static EventManager& Get();
    void PushEvent(const Event& event);
    void PushEvent(SDL_Event& event);

    void PollEvents(std::queue<std::variant<SDL_Event, std::unique_ptr<Event>>>& events);

    void WaitEvents(std::queue<std::variant<SDL_Event, std::unique_ptr<Event>>>& events);
};

}  // namespace event
