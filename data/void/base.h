#pragma once


#include "abyss/include/Window.h"
#include "abyss/include/Audio.h"
#include "abyss/include/GPU.h"
#include "abyss/include/Inet.h"
#include "abyss/include/Input.h"
#include "abyss/include/Render.h"


#include <nlohmann/json.hpp>
#include <filesystem>
#include <functional>
#include <any>
#include <vector>
#include <string>
#include <unordered_map>
#include <math.h>
#include <windows.h>
#include <iostream>
#include <any>
#include <string_view>
#include "sol/sol.hpp"
#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <thread>
#include <atomic>
#include <chrono>
#include <cstdlib>
#include <cstdio>
#include <variant>
#include <type_traits>
#include <iomanip> 




#define DEFAULT "NULL"


using namespace std;

using json = nlohmann::json;
namespace fs = filesystem;

using fint = variant<float,unsigned int,int>;


namespace Resources {
    using namespace std::string_literals;
    
    inline const std::string path_mods = "./mods";
    inline const std::string path_setting  = "./void/settings.json";
    inline const std::string path_system  = "./void/ultima";
    inline const std::string path_system_shaders  = "./void/ultima/shaders";

    inline const std::wstring Title = L"...";
}

