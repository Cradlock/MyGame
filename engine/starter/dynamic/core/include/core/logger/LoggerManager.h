#pragma once


#include "core/boot/BootConfig.h"
#include "core/events/Dispatcher.h"
#include <filesystem>
#include <memory>

namespace spdlog {
  class logger;
};


class Logger{
  private:
    std::filesystem::path m_Log_dir;
    std::shared_ptr<spdlog::logger> m_AsyncLogger;
    const BootConfig* m_Cfg = nullptr; 
    EventDispatcher* m_Dispatcher = nullptr;

  public:
    Logger() = default;
    ~Logger();
  
    void init(const BootConfig*,const std::filesystem::path&,EventDispatcher*);

    void info(std::string_view msg);
    void warn(std::string_view msg);
    void error(std::string_view msg);
    void fatal(std::string_view msg);
  


    void flush();
};


