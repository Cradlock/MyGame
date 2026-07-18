
#include <charconv>
#include <string_view>
#include "core/utils/rini.h"
#include "core/utils/str.h"

ini_value parse_value(std::string_view val) {
    // 1. Сначала пробуем спарсить как int (ноль аллокаций)
    int int_res{};
    auto [p_int, ec_int] = std::from_chars(val.data(), val.data() + val.size(), int_res);
    if (ec_int == std::errc{} && p_int == val.data() + val.size()) {
        return int_res;
    }

    // 2. Пробуем спарсить как double (ноль аллокаций)
    double dbl_res{};
    auto [p_dbl, ec_dbl] = std::from_chars(val.data(), val.data() + val.size(), dbl_res);
    if (ec_dbl == std::errc{} && p_dbl == val.data() + val.size()) {
        return dbl_res;
    }

    // 3. Если это не числа, только ТЕПЕРЬ делаем одну копию в нижнем регистре для проверки bool
    std::string lower_val = str_lower_copy(val); // ОДНА АЛЛОКАЦИЯ
    if (lower_val == "true")  return true;
    if (lower_val == "false") return false;

    // 4. Если это не bool, возвращаем уже созданную строку lower_val 
    // через std::move, чтобы избежать повторного копирования
    return std::move(lower_val);
}

std::unordered_map<std::string, ini_value> read_ini_file(std::ifstream file, BootLogger& logger)
{
    std::unordered_map<std::string, ini_value> storage;
    std::string line;

    while (std::getline(file, line)) {
        std::string_view view = trim(line); 

        if (view.empty() || view[0] == '#' || view.starts_with("//")) {
            continue;
        }

        size_t delim = view.find('=');
        if (delim == std::string_view::npos) {
            continue;
        }

        // Переводим имя в нижний регистр (первая аллокация)
        std::string name = str_lower_copy(trim(view.substr(0, delim)));
        std::string_view val = trim(view.substr(delim + 1));

        // Использование std::move(name) предотвращает копирование ключа внутрь map
        storage[std::move(name)] = parse_value(val);
    }

    return storage;
}

