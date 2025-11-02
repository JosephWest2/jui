#pragma once

#include <format>
#include <functional>
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>
#include "log/logger.hpp"

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_video.h"
#include "input/input_handler.hpp"
#include "window/window.hpp"

const int DEFAULT_FONT_SIZE = 16;

class App {
  protected:
    // SDL
    bool should_quit = false;
    std::vector<std::shared_ptr<window::Window>> windows;
    input::InputHandler input_handler;

    // map from event id to handler (called for all events in the application, delegates to other handlers)
    // the event_id can be a user defined event created using SDL_RegisterEvents
    // if the event has a valid window id, it will only be called for that window, otherwise it is passed to the application handlers
    std::unordered_map<uint32_t, std::function<void(SDL_Event)>> event_handlers {
        {
            SDL_EVENT_QUIT,
            [](SDL_Event e) {
                SDL_Quit();
            }
        },
        {
            SDL_EVENT_WINDOW_CLOSE_REQUESTED,
            [this](SDL_Event e) {
                std::erase_if(windows, [e](std::shared_ptr<window::Window> window) {
                    return window->ID() == e.window.windowID;
                });
            }
        },
        {
            SDL_EVENT_KEY_DOWN,
            [this](SDL_Event e) {
                auto window_id = e.key.windowID;
                if (window_id == window::WINDOW_ID_NULL) {
                    for (auto& [_, handler] : key_down_handlers[e.key.key]) {
                        handler(e.key);
                    }
                }

            }
        },
        {
            SDL_EVENT_KEY_UP,
            [this](SDL_Event e) {
                auto window_id = e.key.windowID;
                if (window_id == window::WINDOW_ID_NULL) {
                    for (auto& [_, handler] : key_up_handlers[e.key.key]) {
                        handler(e.key);
                    }
                }

            }
        },
        {
            SDL_EVENT_MOUSE_MOTION,
            [this](SDL_Event e) {
                auto window_id = e.key.windowID;
                if (window_id == window::WINDOW_ID_NULL) {
                    for (auto& [_, handler] : mouse_motion_handlers) {
                        handler(e.motion);
                    }
                } else {
                    if (auto window = GetWindowByID(window_id)) {
                        window->ExecuteMotionHandler(e.motion);
                    } else {
                        JUI_LOG("Event called on window_id that does not exist: {}", window_id);
                    }
                }
            }
        },
        {
            SDL_EVENT_MOUSE_BUTTON_DOWN,
            [this](SDL_Event e) {
                auto window_id = e.key.windowID;
                if (window_id == window::WINDOW_ID_NULL) {
                    for (auto& [_, handler] : mouse_button_down_handlers) {
                        handler(e.button);
                    }
                } else {
                    if (auto window = GetWindowByID(window_id)) {
                        for (auto& [_, handler] : window->mouse_button_down_handlers) {
                            handler(e.button);
                        }
                    } else {
                        JUI_LOG("Event called on window_id that does not exist: {}", window_id);
                    }
                }

            }
        },
        {
            SDL_EVENT_MOUSE_BUTTON_UP,
            [this](SDL_Event e) {
                auto window_id = e.key.windowID;
                if (window_id == window::WINDOW_ID_NULL) {
                    for (auto& [_, handler] : mouse_button_up_handlers) {
                        handler(e.button);
                    }
                } else {
                    if (auto window = GetWindowByID(window_id)) {
                        for (auto& [_, handler] : window->mouse_button_up_handlers) {
                            handler(e.button);
                        }
                    } else {
                        log::Logger::Get().Log(std::format("Event called on window_id that does not exist: {}", window_id));
                    }
                }

            }
        },
    };

    void RegisterWindowUserEventHandler(std::shared_ptr<window::Window> window, uint32_t event_id, std::function<void(SDL_UserEvent)> handler) {
        window->user_event_handlers[event_id] = handler;
        event_handlers[event_id] = [this](SDL_Event e) {
            if (auto window = GetWindowByID(e.window.windowID)) {
                window->ExecuteUserEventHandler(e.user);
            }
        };
    }

    // map from keycode to handler_id to handler
    std::unordered_map<SDL_Keycode, std::unordered_map<uint32_t, std::function<void(SDL_KeyboardEvent)>>> key_down_handlers;
    // map from keycode to handler_id to handler
    std::unordered_map<SDL_Keycode, std::unordered_map<uint32_t, std::function<void(SDL_KeyboardEvent)>>> key_up_handlers;
    // map from handler id to handler
    std::unordered_map<uint32_t, std::function<void(SDL_MouseButtonEvent)>> mouse_button_down_handlers;
    // map from handler id to handler
    std::unordered_map<uint32_t, std::function<void(SDL_MouseButtonEvent)>> mouse_button_up_handlers;
    // map from handler id to handler
    std::unordered_map<uint32_t, std::function<void(SDL_MouseMotionEvent)>> mouse_motion_handlers;

    void Render();

    bool ShouldPollEvents();

    std::shared_ptr<window::Window> GetWindowByID(SDL_WindowID id);

  public:
    void Run();
    // returns the event id
    uint RegisterCustomEvent(std::function<void(SDL_Event)> handler);
    // return true if event was erased, false if the event was not found
    bool UnRegisterCustomEvent(uint event_id);
    std::shared_ptr<window::Window> CreateWindow(const char* window_title,
                                                 int width,
                                                 int height,
                                                 window::ControlFlow control_flow = window::ControlFlow::WAIT);
    App(const char* app_name, const char* app_version, const char* app_identifier);
    ~App();
};
