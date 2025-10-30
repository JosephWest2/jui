#pragma once

#include <absl/container/flat_hash_map.h>

#include "SDL3_ttf/SDL_ttf.h"

namespace font {

class FontManager {
  protected:
    FontManager() = default;
    ~FontManager() = default;
    FontManager(const FontManager&) = delete;
    FontManager(FontManager&&) = delete;
    FontManager& operator=(const FontManager&) = delete;
    FontManager& operator=(FontManager&&) = delete;

    // map from font name to font size to font
    absl::flat_hash_map<std::string, absl::flat_hash_map<uint, TTF_Font*>> fonts;

  public:
    static FontManager& Get();
    TTF_Font* GetFont(const std::string_view font_name, const uint font_size);
};
}  // namespace font
