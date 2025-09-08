#include "../../include/GPU.h"
#include "../../../pack.h"

void Artifex::createInstance() {
    string file_name = "abyss/src/init_gpu/createInstance.cpp";

    auto check = [file_name](VkResult obj, string error) {
        if (obj != VK_SUCCESS) {
            ErrorNotiffication(error.c_str(), file_name);
        }
    };

    // --- Получаем список доступных слоёв ---
    uint32_t layerCount = 0;
    check(vkEnumerateInstanceLayerProperties(&layerCount, nullptr),
          "Failed to get instance layer count");

    std::vector<VkLayerProperties> availableLayers(layerCount);
    check(vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data()),
          "Failed to enumerate instance layers");

    // --- Проверяем наличие validation layer ---
    const char* validationLayerName = "VK_LAYER_KHRONOS_validation";
    bool validationLayerFound = false;
    for (const auto& layer : availableLayers) {
        if (strcmp(layer.layerName, validationLayerName) == 0) {
            validationLayerFound = true;
            break;
        }
    }

    std::vector<const char*> enabledLayers;
    if (validationLayerFound) {
        enabledLayers.push_back(validationLayerName);
    }

    // --- Получаем доступные расширения ---
    uint32_t ext_count = 0;
    check(vkEnumerateInstanceExtensionProperties(nullptr, &ext_count, nullptr),
          "Failed to get extension count");

    this->extensions_instance.resize(ext_count);
    check(vkEnumerateInstanceExtensionProperties(nullptr, &ext_count, this->extensions_instance.data()),
          "Failed to enumerate extensions");

    std::vector<const char*> extension_names;
    for (const auto& ext : this->extensions_instance) {
        extension_names.push_back(ext.extensionName);
    }

    // --- Настройка приложения ---
    VkApplicationInfo app_info{};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "My Game";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "MyEngine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;
    create_info.enabledLayerCount = static_cast<uint32_t>(enabledLayers.size());
    create_info.ppEnabledLayerNames = enabledLayers.data();
    create_info.enabledExtensionCount = static_cast<uint32_t>(extension_names.size());
    create_info.ppEnabledExtensionNames = extension_names.data();

    // --- Создание VkInstance ---
    check(vkCreateInstance(&create_info, nullptr, &this->instance),
          "Failed to create Vulkan Instance");
}


void Artifex::destroyInstance(){
    if(this->instance) vkDestroyInstance(this->instance, nullptr);
}