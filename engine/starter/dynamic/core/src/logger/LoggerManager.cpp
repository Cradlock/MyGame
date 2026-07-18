


#include "core/logger/LoggerManager.h"
#include "core/boot/BootConfig.h"
#include "core/boot/BootLogger.h"
#include "core/events/Dispatcher.h"
#include "core/rsm/ResManager.h"
#include "sfr/common/events.h"
#include <filesystem>
#include <fmt/base.h>
#include <memory>
#include <spdlog/async_logger.h>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <string_view>
#include <vector>


Logger::~Logger(){
  this->flush();
  spdlog::drop_all();
}




void Logger::init(
BootConfig* cfg,
const std::filesystem::path& dirpath,
EventDispatcher* eventD 
){
  m_Cfg = cfg;  
  m_Log_dir = dirpath / "logs";
  m_Dispatcher = eventD;
  // Работа с spdlog 
  
  if (!std::filesystem::exists(m_Log_dir)) {
        std::filesystem::create_directories(m_Log_dir);
  }
  
  // [1] - Размер очереди сообщений
  // [2] - Количество потоков
  spdlog::init_thread_pool(8192,1);
  
  std::filesystem::path logdir_path = m_Log_dir / "sfr_log.txt"; 
  
  // sinks хранилише
  std::vector<spdlog::sink_ptr> sinks;
  
  
  // Настройка console sink 
  if(m_Cfg && m_Cfg->get<bool>("console",true)){
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();    
    
    console_sink->set_pattern("%^[%T] [%l] %v%$");
    sinks.push_back(console_sink);

  }
  
  // Файловый sink
  int log_maxsize = m_Cfg->get("log_filesize_max",5120 * 1024);
  int log_maxfilecount = m_Cfg->get("log_filecount_max",5);
  
  auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
    logdir_path.string(),
    log_maxsize,
    log_maxfilecount
  ); 
  
  sinks.push_back(rotating_sink); 

  m_AsyncLogger = std::make_shared<spdlog::async_logger>(
    "async_sfr_logger",
    sinks.begin(),
    sinks.end(),
    spdlog::thread_pool(),
    spdlog::async_overflow_policy::block
  );

  m_AsyncLogger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");

  spdlog::register_logger(m_AsyncLogger);
}





void Logger::error(fmt::string_view msg){
  if(m_Dispatcher){
    sfr_event_ctx_t ev{};
    ev.type = SFRE_ERROR_LOG;
    ev.message = msg.data();
    ev.sender = "core:logger_manager";

    m_Dispatcher->broadcast(&ev);
  }

  if(m_AsyncLogger){
    m_AsyncLogger->error(msg);
  } 
}

void Logger::info(fmt::string_view msg){
  if(m_Dispatcher){
    sfr_event_ctx_t ev{};
    ev.type = SFRE_INFO_LOG;
    ev.message = msg.data();
    ev.sender = "core:logger_manager";

    m_Dispatcher->broadcast(&ev);
  }



  if(m_AsyncLogger){
    m_AsyncLogger->info(msg);
  } 
}

void Logger::warn(fmt::string_view msg){
  if(m_Dispatcher){
    sfr_event_ctx_t ev{};
    ev.type = SFRE_WARN_LOG;
    ev.message = msg.data();
    ev.sender = "core:logger_manager";

    m_Dispatcher->broadcast(&ev);
  }



  if(m_AsyncLogger){
    m_AsyncLogger->warn(msg);
  } 
}

void Logger::fatal(fmt::string_view msg){
  if(m_Dispatcher){
    sfr_event_ctx_t ev{};
    ev.type = SFRE_CRITICAL_LOG;
    ev.message = msg.data();
    ev.sender = "core:logger_manager";

    m_Dispatcher->broadcast(&ev);
  }

  if(m_AsyncLogger){
    m_AsyncLogger->critical(msg);
  }  
}

void Logger::flush(){
  if(m_AsyncLogger){
    m_AsyncLogger->flush();
  }
}




