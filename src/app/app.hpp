#pragma once

#include <memory>
#include <queue>
#include <variant>
#include <vector>

#include "event/event.hpp"
#include "input/input_handler.hpp"
#include "window/window.hpp"

const int DEFAULT_FONT_SIZE = 16;

class App {
  protected:
    // SDL
    bool should_quit = false;
    std::vector<std::shared_ptr<window::Window>> windows;
    input::InputHandler input_handler;

    void Render();

    bool ShouldPollEvents();

    void HandleEvents(std::queue<std::variant<SDL_Event, std::unique_ptr<event::Event>>>& event);

  public:
    void Run();
    // returns the event id
    uint RegisterCustomEvent() { return SDL_RegisterEvents(1); }
    std::shared_ptr<window::Window> CreateWindow(const char* window_title,
                                                 int width,
                                                 int height,
                                                 window::ControlFlow control_flow = window::ControlFlow::WAIT);
    App(const char* app_name, const char* app_version, const char* app_identifier);
    ~App();
};
