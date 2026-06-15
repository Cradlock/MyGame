#pragma once





#include "sfr/common/status_codes.h"
#include "sfr/core/logger/types.h"
#include <fstream>
#include <string_view>
#include <filesystem>


class BootConfig;

class BootLogger{
  
  public:
    BootLogger();
    ~BootLogger();

    void log(sfr_type_log_t,std::string_view);
    
    void relocate(const std::filesystem::path&);
    
    void set_cfg(const BootConfig*);
    
  private:

    
    bool m_Debug;
    std::filesystem::path m_Filename; 
    std::ofstream m_FileStream;

    const BootConfig* m_Cfg = nullptr;
};








