




#include "core/Engine.h"
#include "core/config/ConfigManager.h"
#include "core/logger/LoggerManager.h"
#include "core/memory/AllocatorManager.h"
#include "core/rsm/ResManager.h"
#include "core/tick/TickManager.h"
#include "core/utils/pr.h"
#include "core/utils/root.h"
#include "sfr/core/logger/types.h"
#include <exception>
#include <memory>
#include <stdexcept>
#include <string>

Engine::Engine()
{
 
  try{ 
  m_Root_path = get_executable_path().parent_path(); 
  
  m_BootLogger.relocate(m_Root_path);
  
  m_BootConfig.set_dirpath(m_Root_path);
  m_BootConfig.read(m_BootLogger);

  m_BootLogger.set_cfg(&m_BootConfig);

  m_Logger = std::make_unique<Logger>();
  m_Allocator = std::make_unique<Allocator>();
  m_RSM = std::make_unique<RSM>();
  m_Configer = std::make_unique<Configer>();
  m_Ticker = std::make_unique<Ticker>();
  

  std::string version = m_BootConfig.get<std::string>("version");
  LOG_PRINT(version);
  
  } catch(const std::exception& err){
    m_BootLogger.log(SFR_LOG_FATAL, "Error in Engine constructor:" + std::string(err.what()) ); 
  } 

}


