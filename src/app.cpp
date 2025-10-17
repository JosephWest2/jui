#include "app.hpp"

#include <SDL3/SDL.h>

#include <format>
#include <stdexcept>

#include "SDL3_ttf/SDL_ttf.h"

App::App(const char* app_name,
         const char* app_version,
         const char* app_identifier) {
    // Init SDL
    if (!SDL_SetAppMetadata(app_name, app_version, app_identifier)) {
        auto error_msg =
            std::format("Failed to set app metadata: {}", SDL_GetError());
        throw std::runtime_error(error_msg);
    }
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        auto error_msg =
            std::format("Failed to initialize SDL: {}", SDL_GetError());
        throw std::runtime_error(error_msg);
    }
    if (!SDL_CreateWindowAndRenderer(
            app_name, 960, 720, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        auto error_msg = std::format(
            "Failed to create SDL window and renderer: {}", SDL_GetError());
        throw std::runtime_error(error_msg);
    }

    // Init SDL_ttf
    if (!TTF_Init()) {
        SDL_Log("Failed to initialize SDL_ttf: %s", SDL_GetError());
    }
    font = TTF_OpenFont("CousineNerdFont-Regular.ttf", DEFAULT_FONT_SIZE);
    if (!font) {
        auto error_msg = std::format("Failed to load font: {}", SDL_GetError());
        throw std::runtime_error(error_msg);
    }
    text_engine = TTF_CreateRendererTextEngine(renderer);
    if (!text_engine) {
        auto error_msg = std::format("Failed to create SDL_ttf text engine: {}",
                                     SDL_GetError());
        throw std::runtime_error(error_msg);
    }
}

App::~App() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_DestroyRendererTextEngine(text_engine);
}

void App::Run() {
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            quit = input_handler.HandleInput(e);
        }
        if (ui_state.HasChanged()) {
            Render();
        }
    }
}

void App::Render() {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
    ui_state.Render(renderer);
    SDL_RenderPresent(renderer);
}

void App::Add(std::unique_ptr<ui::component::Component>&& component) {
    ui_state.Add(std::move(component));
}
