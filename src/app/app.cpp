#include "app.hpp"

#include <SDL3/SDL.h>

#include <format>
#include <memory>

#include "SDL3/SDL_events.h"
#include "SDL3_ttf/SDL_ttf.h"

App::App(const char* app_name, const char* app_version, const char* app_identifier) {
    // Init SDL
    if (!SDL_SetAppMetadata(app_name, app_version, app_identifier)) {
        auto error_msg = std::format("Failed to set app metadata: {}", SDL_GetError());
        throw std::runtime_error(error_msg);
    }
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        auto error_msg = std::format("Failed to initialize SDL: {}", SDL_GetError());
        throw std::runtime_error(error_msg);
    }
    // Init SDL_ttf
    if (!TTF_Init()) {
        SDL_Log("Failed to initialize SDL_ttf: %s", SDL_GetError());
    }
}

App::~App() { SDL_Quit(); }

void App::Run() {
    SDL_Event event;
    if (!ShouldPollEvents()) {
        SDL_WaitEvent(&event);
        event_handlers[event.type](event);
    }
    while (SDL_PollEvent(&event)) {
        event_handlers[event.type](event);
    }
}

bool App::ShouldPollEvents() {
    for (const auto& window : windows) {
        if (window->GetControlFlow() == window::ControlFlow::POLL) {
            return true;
        }
    }
    return false;
}
std::shared_ptr<window::Window> App::CreateWindow(const char* window_title,
                                                  int width,
                                                  int height,
                                                  window::ControlFlow control_flow) {
    auto window = std::make_shared<window::Window>(window_title, width, height, control_flow);
    windows.push_back(window);
    return window;
}

std::shared_ptr<window::Window> App::GetWindowByID(SDL_WindowID id) {
    for (auto& window : windows) {
        if (window->ID() == id) {
            return window;
        }
    }
    return nullptr;
}

bool App::UnRegisterCustomEvent(uint event_id) {
    if (!event_handlers.contains(event_id)) {
        return false;
    }
    event_handlers.erase(event_id);
    return true;
}

uint App::RegisterCustomEvent(std::function<void(SDL_Event)> handler) {
    uint event_id = SDL_RegisterEvents(1);
    event_handlers[event_id] = handler;
    return event_id;
}
