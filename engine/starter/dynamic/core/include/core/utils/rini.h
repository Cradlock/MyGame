
#include "core/boot/BootLogger.h"
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <fstream>

using ini_value = std::variant<int, double, std::string, bool>;

// Вспомогательная функция для парсинга значений
ini_value parse_value(std::string_view val); 

std::unordered_map<std::string, ini_value> read_ini_file(std::ifstream file, BootLogger& logger);

