

#include "core/boot/BootConfig.h"
#include "core/boot/BootLogger.h"
#include "core/utils/str.h"
#include "sfr/core/logger/types.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>
BootConfig::BootConfig()
: m_Filename(".config_cfg.ini"){

}

void BootConfig::set_dirpath(
  const std::filesystem::path& path
){
  m_Filename = path / ".config.ini"; 
}

void BootConfig::read(BootLogger& logger){
 
  if (m_Filename.empty()) {
    logger.log(SFR_LOG_FATAL, "BootConfig: Directory path was not set before calling read()!");
    return;
  } 

  std::ifstream file(m_Filename);
  


  if(!file.is_open()){
    logger.log(SFR_LOG_FATAL,"Boot config not found!: Use Default settings"); 
    return;
  }

     
  
  file.close(); 
  
}





