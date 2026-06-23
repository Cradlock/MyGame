



#include "core/boot/BootLogger.h"
#include "core/boot/BootConfig.h"
#include "core/utils/pr.h"
#include "core/utils/time.h"
#include "sfr/core/logger/types.h"
#include <ios>
#include <string_view>

BootLogger::BootLogger() 
: m_Debug(false)
{   

  m_Filename = std::filesystem::path(get_formatted_time("%d-%m-%Y_%H-%M-%S")+".bootlog.txt");
  
  this->m_FileStream.open(m_Filename, std::ios::out);

  if (m_FileStream.is_open()) {
    if(m_Debug) m_FileStream << "=== SANDFORM ENGINE BOOTLOG INITIATED ===\n";
    m_FileStream.flush();
  }

}



BootLogger::~BootLogger(){
    if (m_FileStream.is_open()) {
        if(m_Debug) m_FileStream << "=== SANDFORM ENGINE BOOTLOG CLOSED ===\n";
        
        m_FileStream.close(); // Безопасно закрываем файл при уничтожении логгера
    }
}

void BootLogger::log(
  sfr_type_log_t type,std::string_view msg
)  {

    std::string_view level_str = "[UNKNOWN]";
    switch (type) {
        case SFR_LOG_INFO:    level_str = "[INFO] "; break;
        case SFR_LOG_WARNING: level_str = "[WARN] "; break;
        case SFR_LOG_ERROR:   level_str = "[ERROR] "; break;
        case SFR_LOG_FATAL:   level_str = "[FATAL] "; break;
    }

    m_FileStream << level_str << msg << "\n";
    m_FileStream.flush();

}


void BootLogger::relocate(
  const std::filesystem::path& new_dir
){
  if (m_FileStream.is_open()) {
      if(m_Debug) m_FileStream << "[SYSTEM] Relocating bootlog to target logs directory...\n";
      m_FileStream.close();
  }

    std::filesystem::path old_path = m_Filename;
    std::filesystem::path new_path = new_dir / old_path.filename();

    std::error_code ec;
    std::filesystem::rename(old_path, new_path, ec);

    if (!ec) {
        m_Filename = new_path;
    } else {
        m_Filename = old_path; 
    }

    m_FileStream.open(m_Filename, std::ios::out | std::ios::app);
    
    if (m_FileStream.is_open()) {
        if(m_Debug) m_FileStream << "[SYSTEM] Bootlog successfully relocated and reopened.\n";
        m_FileStream.flush();
    }
}



void BootLogger::set_cfg(const BootConfig* cfg){
  m_Cfg = cfg;

try {
    m_Debug = m_Cfg->get<bool>("harddebug");
} catch (const std::out_of_range&) {
    m_Debug = true;
}
  
}






