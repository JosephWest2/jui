#pragma once

#include <sys/types.h>

#include <cassert>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "SDL3/SDL_video.h"
#include "component/component.hpp"
#include "window/renderer/renderer.hpp"

using std::optional;
using std::pair;
using std::runtime_error;
using std::string;
using std::vector;

namespace window {

using component::Component;
using renderer::Renderer;

enum class ControlFlow { WAIT, POLL };

class Window {
  protected:
    vector<Component> components;
    ControlFlow control_flow{ControlFlow::WAIT};
    bool window_redraw_needed{true};
    SDL_Window* window;
    optional<Renderer> renderer;

  public:
    ~Window();
    void Draw();

    Window(const char* window_title, int width, int height, ControlFlow control_flow);

    const char* Title() const;

    // returns {width, height}
    pair<int, int> GetDimensions() const;
    int GetWidth() const;
    int GetHeight() const;
};

}  // namespace window
