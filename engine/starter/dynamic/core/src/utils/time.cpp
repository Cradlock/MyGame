


#include "core/utils/time.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <string_view>
std::string get_formatted_time(const char* fmtl){
  
  auto now = std::chrono::system_clock::now();

  auto time_c = std::chrono::system_clock::to_time_t(now);

  std::tm local_tm;

#if defined (_WIN32)
  localtime_s(&local_tm, &time_c);
#else
  localtime_r(&time_c, &local_tm);
#endif


  std::ostringstream oss;
  oss << std::put_time(&local_tm, fmtl); 
    
  return oss.str();
}

