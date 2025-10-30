#include "app.hpp"

#include <SDL3/SDL.h>

#include <format>
#include <memory>
#include <queue>
#include <variant>

#include "SDL3/SDL_events.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "event/event.hpp"
#include "event/event_manager.hpp"
#include "event/window_redraw_request.hpp"

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
    std::queue<std::variant<SDL_Event, std::unique_ptr<event::Event>>> events;
    while (!should_quit) {
        if (ShouldPollEvents()) {
            event::EventManager::Get().PollEvents(events);
        } else {
            event::EventManager::Get().WaitEvents(events);
        }
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
void App::HandleEvents(std::queue<std::variant<SDL_Event, std::unique_ptr<event::Event>>>& events) {
    while (!events.empty()) {
        auto event = std::move(events.front());
        events.pop();
        if (std::holds_alternative<std::unique_ptr<event::Event>>(event)) {
            auto custom_event = std::move(std::get<std::unique_ptr<event::Event>>(event));
            if (auto event = dynamic_cast<event::WindowRedrawRequest*>(custom_event.get())) {
                for (auto& window : windows) {
                    if (window->ID() == event->window_id) {
                        window->RequestRedraw();
                    }
                }
            }
        } else {
            auto sdl_event = std::get<SDL_Event>(event);
            switch (sdl_event.type) {
                case SDL_EVENT_QUIT:
                    should_quit = true;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    input_handler.HandleKeyDown(sdl_event.key);
                    break;
                case SDL_EVENT_KEY_UP:
                    input_handler.HandleKeyUp(sdl_event.key);
                    break;
                case SDL_EVENT_MOUSE_MOTION:
                    input_handler.HandleMouseMotion(sdl_event.motion);
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    input_handler.HandleMouseDown(sdl_event.button);
                    break;
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    input_handler.HandleMouseUp(sdl_event.button);
                    break;
                case SDL_EVENT_MOUSE_WHEEL:
                    input_handler.HandleMouseWheel(sdl_event.wheel);
                    break;
            }
        }
    }
    for (auto& window : windows) {
        window->DrawIfNeeded();
    }
}
std::shared_ptr<window::Window> App::CreateWindow(const char* window_title,
                                                  int width,
                                                  int height,
                                                  window::ControlFlow control_flow) {
    auto window = std::make_shared<window::Window>(window_title, width, height, control_flow);
    windows.push_back(window);
    return window;
}

