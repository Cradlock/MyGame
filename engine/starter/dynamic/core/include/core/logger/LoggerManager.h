#pragma once


#include "core/boot/BootConfig.h"
#include "core/events/Dispatcher.h"
#include <filesystem>
#include <fmt/base.h>
#include <memory>

namespace spdlog {
  class logger;
};


class Logger{
  private:
    std::filesystem::path m_Log_dir;
    std::shared_ptr<spdlog::logger> m_AsyncLogger;
    BootConfig* m_Cfg = nullptr; 
    EventDispatcher* m_Dispatcher = nullptr;

  public:
    Logger() = default;
    ~Logger();
  
    void init(BootConfig*,const std::filesystem::path&,EventDispatcher*);

    void info(fmt::string_view msg);
    void warn(fmt::string_view msg);
    void error(fmt::string_view msg);
    void fatal(fmt::string_view msg);
  


    void flush();
};


