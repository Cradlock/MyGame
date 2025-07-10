#include "../include/GPU.h"
#include "../../pack.h"

#ifndef UNICODE
#define UNICODE
#endif 



Artifex::Artifex(PanarchonWindow& wind) 
: physical_device(VK_NULL_HANDLE),queue_priority(1.0f),window(&wind)
{

    vkEnumerateInstanceExtensionProperties(nullptr,&this->extensionCount,nullptr);
    // определение возможностей видеокарт
    this->extensions = vector<VkExtensionProperties>(this->extensionCount); 
    vkEnumerateInstanceExtensionProperties(nullptr,&this->extensionCount,this->extensions.data());

// обшая инфромация об работе с драйверами
    this->app_info = {};
    this->app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    this->app_info.pApplicationName = "Default applicationName";
    this->app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    this->app_info.pEngineName = "Default engine name";
    this->app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    this->app_info.apiVersion = VK_API_VERSION_1_0;


    vector<const char*> req_extensions = {};
    for(const auto& ext : this->extensions){
        if(strcmp(ext.extensionName, "VK_KHR_surface") == 0){
            req_extensions.push_back(ext.extensionName);
            continue;
        }

        if(strcmp(ext.extensionName,"VK_KHR_swapchain") == 0){
            req_extensions.push_back(ext.extensionName);
            continue;
        }

#ifdef _WIN32
        if (strcmp(ext.extensionName, "VK_KHR_win32_surface") == 0) {
            req_extensions.push_back("VK_KHR_win32_surface");
            continue;
        }
#endif

    }

    VkInstanceCreateInfo connect_info = {};
    connect_info = {};
    connect_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    connect_info.pApplicationInfo = &this->app_info;
    connect_info.enabledExtensionCount = 2;
    connect_info.ppEnabledExtensionNames = req_extensions.data();
    connect_info.enabledLayerCount = 0;


    VkResult result = vkCreateInstance(&connect_info,nullptr,&this->connect);

    if(result != VK_SUCCESS){
       ErrorNotiffication("Unable create VkInstance","In Abyss/GPU.cpp Artifex constructor");   
    }
  

// Получение всех видеокарт 
    vkEnumeratePhysicalDevices(this->connect,&this->device_count, nullptr);
    if(!this->device_count){
        ErrorNotiffication("Not connected with vulkan","Abyss/GPU.cpp constructor artifex");
    }
    this->devices = vector<VkPhysicalDevice>(this->device_count);
    vkEnumeratePhysicalDevices(this->connect,&this->device_count, this->devices.data());

    
// Инфромация о графическом устройстве
    // обшая
    VkPhysicalDeviceProperties device_propt;

    // подробно
    // VkPhysicalDeviceFeatures device_features;
    
    int score = 0;
    int best_score = 0;
// Выбор определенного устройства
    for(const auto& device : this->devices){
        vkGetPhysicalDeviceProperties(device,&device_propt);

        switch (device_propt.deviceType) {
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:  score += 1000; break;
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: score += 500; break;
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:    score += 100; break;
        case VK_PHYSICAL_DEVICE_TYPE_CPU:            score += 10; break;
        default: break;
        }

        score += device_propt.limits.maxImageDimension2D;

        if(score > best_score){
            best_score = score;
            this->physical_device = device;
        }

    }

    if(this->physical_device == VK_NULL_HANDLE){
        cout << "Not connected with GPU :" << endl;
    }

     this->index_family = this->select_queue(this->physical_device);

    VkDeviceQueueCreateInfo queue_info = {};
    queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_info.queueFamilyIndex = this->index_family;
    queue_info.queueCount = 1;
    queue_info.pQueuePriorities = &this->queue_priority;
    
    VkDeviceCreateInfo virtual_device_info = {};
    virtual_device_info.sType =  VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    virtual_device_info.queueCreateInfoCount = 1;
    virtual_device_info.pQueueCreateInfos = &queue_info;

    if(vkCreateDevice(this->physical_device,&virtual_device_info,nullptr,&this->virtual_device ) != VK_SUCCESS){
        ErrorNotiffication("Unable create logic device","in abyss/GPU.cpp");
    }
    
    vkGetDeviceQueue(this->virtual_device,this->index_family,0,&this->graphic_queue);
    
    this->createSurface();


}


void Artifex::destroy(){
    vkDestroySurfaceKHR(this->connect,this->surface,nullptr);
    vkDestroyInstance(this->connect,nullptr);
}




void Artifex::setAppName(string val){
    this->app_info.pApplicationName = val.c_str();
}

void Artifex::setEngineName(string val){
    this->app_info.pEngineName = val.c_str();
}



uint32_t Artifex::select_queue(VkPhysicalDevice& device){
   uint32_t family_count = 0;
   
   vkGetPhysicalDeviceQueueFamilyProperties(device,&family_count,nullptr);
   if(!family_count) return UINT32_MAX;

   vector<VkQueueFamilyProperties> families(family_count);
   vkGetPhysicalDeviceQueueFamilyProperties(device,&family_count,families.data());

   for( int i = 0; i < family_count ;++i ){
       if( families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT ){
         return i;
       }
   }
   

   return UINT32_MAX;
}


#ifdef _WIN32

void Artifex::createSurface(){
   if(this->window == nullptr){
        ErrorNotiffication("Not found window","in abyss/GPU.cpp/Artifex/createSurface");
        exit(EXIT_FAILURE);
   }

    // for(const auto&  ext : this->extensions ){
    //     cout << ext.extensionName << endl;
    // }

    VkWin32SurfaceCreateInfoKHR surface_info = {};
    surface_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    surface_info.hwnd = this->window->getMainWindow();
    surface_info.hinstance = this->window->gethInstance();

    

    if(vkCreateWin32SurfaceKHR(this->connect,&surface_info,nullptr,&this->surface) != VK_SUCCESS ){
       ErrorNotiffication("Failed to create SURFACE","in abyss/GPU.cpp/Artifex/createSurface");
       exit(EXIT_FAILURE);
    }
}


#endif
