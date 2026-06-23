#pragma once 




#include "core/boot/BootLogger.h"
#include <filesystem>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
class BootConfig{

  private:
    std::filesystem::path m_Filename;
    std::unordered_map<
      std::string, 
      std::variant<bool,std::string,int>> m_Storage;     

  public:
    BootConfig();
  
    template <typename T>
    T get(std::string_view key) const {
        std::string k(key);
        auto it = m_Storage.find(k);
        
        if (it == m_Storage.end()) {
            throw std::out_of_range("BootConfig::get(): Critical key '" + k + "' not found!");
        }

        // std::get<T> автоматически вытащит нужный тип из variant
        
        return std::get<T>(it->second);
    }

    template <typename T>
    T get(std::string_view key, const T& default_value) {
        std::string k(key);
        auto it = m_Storage.find(k);

        // Если ключ найден, просто возвращаем его значение
        if (it != m_Storage.end()) {
            return std::get<T>(it->second);
        }

        // Если ключа нет — АВТОЗАПОЛНЕНИЕ:
        m_Storage[k] = default_value; 
        
        // Возвращаем дефолтное значение
        return default_value;
    }
    

    void set_dirpath(const std::filesystem::path&); 
    
    void read(BootLogger&);    

  
};



