#pragma once

#include <string>
#include <unordered_map>
#include "font/font.hpp"

using std::unordered_map;
using std::string;

namespace font {

class FontManager {
  private:
    FontManager() = default;
    ~FontManager() = default;
    FontManager(const FontManager&) = delete;
    FontManager(FontManager&&) = delete;
    FontManager& operator=(const FontManager&) = delete;
    FontManager& operator=(FontManager&&) = delete;

    // map from font name to font size to font
    unordered_map<string, unordered_map<uint, Font>> fonts;

  public:
    static FontManager& Get() {
        static FontManager instance;
        return instance;
    }

    
};
}  // namespace font
