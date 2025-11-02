#pragma once

#include <sys/types.h>

#include <cassert>
#include <functional>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

#include "SDL3/SDL_video.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "component/component.hpp"
#include "component/logical/logical_component.hpp"
#include "window/renderer/renderer.hpp"

namespace event {
class Event;
}

namespace window {

constexpr uint WINDOW_ID_NULL = 0;

enum class ControlFlow { WAIT, POLL };

class Window : public std::enable_shared_from_this<Window> {
  protected:
    std::vector<std::shared_ptr<component::Component>> components;
    ControlFlow control_flow{ControlFlow::WAIT};
    SDL_Window* window;
    std::optional<renderer::Renderer> renderer;
    bool window_redraw_needed{true};
    void Draw();

    std::vector<std::shared_ptr<component::logical::LogicalComponent>> logical_components;


  public:
    ~Window();

    // map from event id (reveived from SDL_RegisterEvents) to handler with opaque user data as an argument
    std::unordered_map<uint32_t, std::function<void(SDL_UserEvent)>> user_event_handlers;
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

    void ExecuteMotionHandler(SDL_MouseMotionEvent& e) {
        for (auto& [_, handler] : mouse_motion_handlers) {
            handler(e);
        }
    }

    void ExecuteMouseDownHandler(SDL_MouseButtonEvent& e) {
        for (auto& [_, handler] : mouse_button_down_handlers) {
            handler(e);
        }
    }

    void ExecuteMouseUpHandler(SDL_MouseButtonEvent& e) {
        for (auto& [_, handler] : mouse_button_up_handlers) {
            handler(e);
        }
    }

    void ExecuteKeyDownHandler(SDL_KeyboardEvent& e) {
        for (auto& [_, handler] : key_down_handlers[e.key]) {
            handler(e);
        }
    }

    void ExecuteKeyUpHandler(SDL_KeyboardEvent& e) {
        for (auto& [_, handler] : key_up_handlers[e.key]) {
            handler(e);
        }
    }

    void ExecuteUserEventHandler(SDL_UserEvent& e) {
        if (user_event_handlers.contains(e.type)) {
            user_event_handlers[e.type](e);
        }
    }

    inline void RequestRedraw() { window_redraw_needed = true; }
    void DrawIfNeeded();

    Window(const char* window_title, int width, int height, ControlFlow control_flow);

    void RegisterComponent(std::shared_ptr<component::Component>& component);

    bool ContainsComponent(std::shared_ptr<component::Component>& component);

    void AddLogicalComponent(std::shared_ptr<component::logical::LogicalComponent>& logical_component) {
        logical_components.push_back(logical_component);
    };

    TTF_TextEngine* text_engine;

    // returns {width, height}
    std::pair<int, int> GetDimensions() const;
    inline int GetWidth() const { return GetDimensions().first; }
    inline int GetHeight() const { return GetDimensions().second; }
    inline ControlFlow GetControlFlow() const { return control_flow; }
    inline SDL_WindowID ID() const { return SDL_GetWindowID(window); }
    inline const char* Title() const { return SDL_GetWindowTitle(window); }
};

}  // namespace window
