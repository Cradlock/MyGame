
#pragma once
#include <string>
#include <string_view>

std::string_view trim(std::string_view str);
std::string trim_copy(std::string_view str);
void trim_inplace(std::string& str);
void str_lower_inplace(std::string& value);
std::string str_lower_copy(std::string_view value);
