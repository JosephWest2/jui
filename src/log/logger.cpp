#include "logger.hpp"
#include <format>
#include "SDL3/SDL_log.h"

namespace log {

Logger& Logger::Get() {
    static Logger instance;
    return instance;
}
void Logger::Log(const std::string_view& message) {
    SDL_Log("%s", message.data());
}

template <typename... Args>
void Logger::Log(const std::string_view& fmt, const Args&... args) {
    Log(std::format(fmt, args...));

};

}  // namespace log
