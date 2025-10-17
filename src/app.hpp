#pragma once

#include <memory>

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "input/handler.hpp"
#include "ui/component/component.hpp"
#include "ui/state.hpp"

const int DEFAULT_FONT_SIZE = 16;

class App {
  private:
    // SDL
    SDL_Renderer* renderer;
    SDL_Window* window;
    TTF_Font* font;
    TTF_TextEngine* text_engine;

    ui::State ui_state;
    input::Handler input_handler;

    void Render();

  public:
    void Run();
    void Add(std::unique_ptr<ui::component::Component>&& component);
    App(const char* app_name,
        const char* app_version,
        const char* app_identifier);
    ~App();
};
