#include "../../include/GPU.h"
#include "../../../pack.h"

void Artifex::createInstance(){
    string file_name = "abyss/src/init_gpu/createInstance.cpp";

    auto check = [file_name](VkResult obj,string error){
        if(obj != VK_SUCCESS){
            ErrorNotiffication(error.c_str(),file_name);
        }
    };
    

    uint32_t ext_count = 0;
    check(
        vkEnumerateInstanceExtensionProperties(nullptr, &ext_count, nullptr),
        "Failed to get extension count"
    );
     
    this->extensions_instance.resize(ext_count);

    check(
        vkEnumerateInstanceExtensionProperties(nullptr,&ext_count,this->extensions_instance.data()),
        "Failed to enumerate all extensions"
    );


    vector<const char*> validation_layer = {"VK_LAYER_KHRONOS_validation"};
    
    VkApplicationInfo app_info = {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "My Game";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "MyEngine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_3;


    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;
    create_info.enabledLayerCount = static_cast<uint32_t>(validation_layer.size());
    create_info.ppEnabledLayerNames = validation_layer.data();
    
    vector<const char*> extension_names;
    for(const auto& ext : this->extensions_instance){
        extension_names.push_back(ext.extensionName);
    }

    create_info.enabledExtensionCount = static_cast<uint32_t>(extension_names.size());
    create_info.ppEnabledExtensionNames = extension_names.data();

    check(
        vkCreateInstance(&create_info, nullptr, &this->instance),
        "Failed to create vkInstance object"
    );

}



void Artifex::destroyInstance(){
    if(this->instance) vkDestroyInstance(this->instance, nullptr);
}