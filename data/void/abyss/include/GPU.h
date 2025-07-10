#pragma once

#ifndef UNICODE
#define UNICODE
#endif 

#include "Window.h"
#include "vulkan/vulkan.h"
#include <vulkan/vulkan_win32.h>
#include <vector>





class Artifex{
private:

   uint32_t extensionCount;
   VkInstance connect;
   VkApplicationInfo app_info;
   
   // Расширения для работы с Vulkan
   vector<VkExtensionProperties> extensions;
   
   // физическое устройство
   uint32_t device_count;
   VkPhysicalDevice physical_device;

   // Логическое устройство
   float queue_priority;
   VkDevice virtual_device; 

   //Очередь
   VkQueue graphic_queue;    


   // Список графических устройств
   vector<VkPhysicalDevice> devices;

   // Индекс выбранного семейства
   uint32_t index_family;

   // связь с поерхностью где нужно рисовать
   PanarchonWindow* window = nullptr;
   VkSurfaceKHR surface;



public:

Artifex(PanarchonWindow& wind);

inline uint32_t getExtCount() const { return this->extensionCount; };
void setAppName(string value);
void setEngineName(string value);
void destroy();



inline void info_device(VkPhysicalDevice& device){
   VkPhysicalDeviceProperties properties;
   vkGetPhysicalDeviceProperties(device,&properties);
   cout << "==============================\n";
    cout << " Device Name       : " << properties.deviceName << endl;
    cout << " Device Type       : ";

    switch (properties.deviceType) {
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:  cout << "Integrated GPU"; break;
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:    cout << "Discrete GPU"; break;
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:     cout << "Virtual GPU"; break;
        case VK_PHYSICAL_DEVICE_TYPE_CPU:             cout << "CPU"; break;
        default:                                      cout << "Other / Unknown"; break;
    }
    cout << endl;

    cout << " API Version       : "
         << VK_VERSION_MAJOR(properties.apiVersion) << "."
         << VK_VERSION_MINOR(properties.apiVersion) << "."
         << VK_VERSION_PATCH(properties.apiVersion) << endl;

    cout << " Driver Version    : "
         << VK_VERSION_MAJOR(properties.driverVersion) << "."
         << VK_VERSION_MINOR(properties.driverVersion) << "."
         << VK_VERSION_PATCH(properties.driverVersion) << endl;

    cout << " Max Image Dimension 2D : " << properties.limits.maxImageDimension2D << endl;
    cout << " Max Uniform Buffer Range: " << properties.limits.maxUniformBufferRange << endl;
    cout << " Max Vertex Input Attributes: " << properties.limits.maxVertexInputAttributes << endl;
    cout << " Max Push Constants Size: " << properties.limits.maxPushConstantsSize << " bytes" << endl;

    cout << " Timestamp Period         : " << properties.limits.timestampPeriod << " ns" << endl;
   
    cout << " Non-Coherent Atom Size   : " << properties.limits.nonCoherentAtomSize << endl;

    cout << "==============================\n";
}


uint32_t select_queue(VkPhysicalDevice& device);

void createSurface();


};