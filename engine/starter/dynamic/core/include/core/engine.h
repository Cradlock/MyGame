#pragma once

#include "core/boot/BootConfig.h"
#include "core/boot/BootLogger.h"
#include "core/config/ConfigManager.h"
#include "core/events/Dispatcher.h"
#include "core/logger/LoggerManager.h"
#include "core/memory/AllocatorManager.h"
#include "core/rsm/ResManager.h"
#include "core/tick/TickManager.h"
#include "sfr/common/engine.h"
#include <filesystem>
#include <memory>


class Engine{
private:
// Сервисы
  BootConfig m_BootConfig;
  BootLogger m_BootLogger;
  
  std::unique_ptr<EventDispatcher> m_EventDispatcher;

  std::unique_ptr<Allocator> m_Allocator;
  std::unique_ptr<Logger> m_Logger;
  std::unique_ptr<RSM> m_RSM; 
  

  std::unique_ptr<Configer> m_Configer;
  std::unique_ptr<Ticker> m_Ticker; 
  


public:
  Engine();
  
  void Init();

  void Run();

  void Shutdown();
  

  sfr_engine_context_t createAPIContext();

private:
  
  std::filesystem::path m_Root_path;
  

};




