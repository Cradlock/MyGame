

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

  std::string line;
    
  while ( std::getline(file,line) ) {

    line = trim(line);
    
    if (line.empty() || line[0] == '#' || line.substr(0,2) == "//") {
      continue;
    }

    size_t delimiter_pos = line.find('=');
    if(delimiter_pos == std::string::npos){
      continue;
    }

    std::string name  = line.substr(0, delimiter_pos);
    std::string value = line.substr(delimiter_pos + 1);

    name  = str_lower(trim(name));
    value = trim(value);
    
    std::string check_bool = str_lower(value);

    if (check_bool == "true")       m_Storage[name] = true;
    else if (check_bool == "false") m_Storage[name] = false;
    else {
        try {
            size_t processed_chars = 0;
            
            // 1. Сначала пробуем спарсить как INT
            int parsed_int = std::stoi(value, &processed_chars);
            if (processed_chars == value.size()) {
                m_Storage[name] = parsed_int;
                continue; // Успешно записали int, идем к следующей строке
            }

            // 2. Если int не сожрал всю строку (например, помешала точка '4.0'), пробуем DOUBLE
            size_t processed_double_chars = 0;
            double parsed_double = std::stod(value, &processed_double_chars);
            if (processed_double_chars == value.size()) {
                m_Storage[name] = parsed_double;
                continue; // Успешно записали double
            }

            // 3. Если это и не int, и не double (какой-то мусор типа "44.22.11"), сохраняем как строку
            m_Storage[name] = value;

        }
        catch (...) {
            m_Storage[name] = value; 
        }
      }   

  }
    
  
  file.close(); 
  
}





