#pragma once



#include <string>
#include <cctype>
#include <algorithm>

// 1. Реализация string_view trim
// Работает за O(1), не выделяет память, просто двигает указатели начала и конца.
std::string_view trim(std::string_view str) {
    const std::string_view whitespace = " \t\r\n";
    
    size_t first = str.find_first_not_of(whitespace);
    if (first == std::string_view::npos) {
        return {}; // Возвращает пустой string_view
    }
    
    size_t last = str.find_last_not_of(whitespace);
    return str.substr(first, (last - first + 1));
}

// 2. Реализация trim_copy
// Принимает string_view (чтобы можно было передать и литерал, и std::string), 
// но на выходе принудительно создаёт и возвращает новый объект std::string.
std::string trim_copy(std::string_view str) {
    return std::string(trim(str));
}

// 3. Реализация trim_inplace
// Физически удаляет пробелы из переданной строки std::string, уменьшая её размер.
void trim_inplace(std::string& str) {
    const std::string_view whitespace = " \t\r\n";
    
    size_t first = str.find_first_not_of(whitespace);
    if (first == std::string::npos) {
        str.clear();
        return;
    }
    
    size_t last = str.find_last_not_of(whitespace);
    
    // Переносим данные в начало строки и обрезаем лишнее
    if (first > 0 || last < str.size() - 1) {
        str = str.substr(first, (last - first + 1));
    }
}



void str_lower_inplace(std::string& value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
}

std::string str_lower_copy(std::string_view value) {
    std::string result;
    result.resize(value.size()); // Сразу выделяем память нужного размера, избегая realloc-ов
    
    std::transform(value.begin(), value.end(), result.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    
    return result;
}




