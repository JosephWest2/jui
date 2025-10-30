#pragma once

#include <string_view>
namespace log {

class Logger {
  private:
    Logger() = default;
    ~Logger() = default;

  public:
    static Logger& Get();
    void Log(const std::string_view& message);
};

}  // namespace log
