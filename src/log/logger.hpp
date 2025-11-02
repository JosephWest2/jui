#pragma once

#define JUI_LOG(...) log::Logger::Get().Log(__VA_ARGS__)

#include <string_view>
namespace log {

class Logger {
  private:
    Logger() = default;
    ~Logger() = default;

  public:
    static Logger& Get();
    void Log(const std::string_view& message);
    template <typename... Args>
    void Log(const std::string_view& fmt, const Args&... args);
};

}  // namespace log
