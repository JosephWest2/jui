#include "font_manager.hpp"
namespace font {

FontManager& font::FontManager::Get() {
    static FontManager instance;
    return instance;
}

TTF_Font* FontManager::GetFont(const std::string_view font_name, const uint font_size) {
    if (!fonts.contains(font_name)) {
        fonts[font_name] = {};
    }
    if (!fonts[font_name].contains(font_size)) {
        fonts[font_name][font_size] = TTF_OpenFont(font_name.data(), font_size);
    }
    if (fonts.contains(font_name)) {
        if (fonts[font_name].contains(font_size)) {
            return fonts[font_name][font_size];
        }
    }
    return nullptr;
}
}  // namespace font
