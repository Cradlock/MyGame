


#include "core/logger/LoggerManager.h"
#include "core/boot/BootConfig.h"
#include "core/boot/BootLogger.h"
#include "core/events/Dispatcher.h"
#include <filesystem>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>

Logger::~Logger(){

}




void Logger::init(
const BootConfig* cfg,
const std::filesystem::path& dirpath,
EventDispatcher* eventD 
){
  m_Cfg = cfg;  
  m_Log_dir = dirpath / "logs";
  m_Dispatcher = eventD;
  // Работа с spdlog 

  // [1] - Размер очереди сообщений
  // [2] - Количество потоков
  spdlog::init_thread_pool(8192,1);

  
  std::filesystem::path logdir_path = m_Log_dir / "/logs"; 
  

  
}














