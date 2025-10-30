#pragma once

#include <sys/types.h>

#include <cassert>
#include <optional>
#include <utility>
#include <vector>

#include "SDL3/SDL_video.h"
#include "component/component.hpp"
#include "component/logical/logical_component.hpp"
#include "window/renderer/renderer.hpp"

namespace window {

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

    inline void RequestRedraw() { window_redraw_needed = true; }
    void DrawIfNeeded();

    Window(const char* window_title, int width, int height, ControlFlow control_flow);

    void RegisterComponent(std::shared_ptr<component::Component>& component);

    bool ContainsComponent(std::shared_ptr<component::Component>& component);

    void AddLogicalComponent(std::shared_ptr<component::logical::LogicalComponent>& logical_component) {
        logical_components.push_back(logical_component);
    };

    // returns {width, height}
    std::pair<int, int> GetDimensions() const;
    inline int GetWidth() const { return GetDimensions().first; }
    inline int GetHeight() const { return GetDimensions().second; }
    inline ControlFlow GetControlFlow() const { return control_flow; }
    inline SDL_WindowID ID() const { return SDL_GetWindowID(window); }
    inline const char* Title() const { return SDL_GetWindowTitle(window); }
};

}  // namespace window
