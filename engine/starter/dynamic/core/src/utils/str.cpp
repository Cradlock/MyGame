

#include <algorithm>
#include <string>


#include "core/utils/str.h"

std::string trim(const std::string& str){
  size_t first = str.find_first_not_of(" \t\r\n");
  if (first == std::string::npos) return "";
  size_t last = str.find_last_not_of(" \t\r\n");
  return str.substr(first, (last - first + 1));
}



std::string str_lower(std::string value){
  std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
    return std::tolower(c);
  });    

  return value;
}




