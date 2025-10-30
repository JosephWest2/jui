#include "event_manager.hpp"

#include "SDL3/SDL_events.h"

namespace event {

EventManager::EventManager() : custom_event_id(SDL_RegisterEvents(1)) {};

EventManager& EventManager::Get() {
    static EventManager instance;
    return instance;
}
void EventManager::PollEvents(std::queue<std::variant<SDL_Event, std::unique_ptr<Event>>>& events) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == custom_event_id) {
            events.push(std::unique_ptr<Event>(reinterpret_cast<Event*>(e.user.data1)));
        } else {
            events.push(e);
        }
    }
}
void EventManager::WaitEvents(std::queue<std::variant<SDL_Event, std::unique_ptr<Event>>>& events) {
    SDL_Event e;
    SDL_WaitEvent(&e);
    if (e.type == custom_event_id) {
        events.push(std::unique_ptr<Event>(reinterpret_cast<Event*>(e.user.data1)));
    } else {
        events.push(e);
    }
    PollEvents(events);
}
void EventManager::PushEvent(const Event& event) {
    Event* event_data = new Event(event);
    SDL_Event e;
    e.type = custom_event_id;
    e.user.data1 = &event_data;
    SDL_PushEvent(&e);
}
void EventManager::PushEvent(SDL_Event& event) {
    SDL_PushEvent(&event);
};
}  // namespace event
