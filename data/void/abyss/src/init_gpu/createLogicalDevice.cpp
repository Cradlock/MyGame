#include "../../include/GPU.h"
#include "../../../pack.h"


void Artifex::createLogicalDevice(){
    string file_name = "abyss/src/init_gpu/createLogicallDevice.cpp";

    auto check = [file_name](VkResult obj,string error){
        if(obj != VK_SUCCESS){
            ErrorNotiffication(error.c_str(),file_name);
        }
    };


    float queue_priority = 1.0f;
    vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    
    VkDeviceQueueCreateInfo graphics_q_info{};
    graphics_q_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    graphics_q_info.queueFamilyIndex = this->select_indices.graphicIndex.value();
    graphics_q_info.queueCount = 1;
    graphics_q_info.pQueuePriorities = &queue_priority;

    queueCreateInfos.push_back(graphics_q_info);

    if(this->select_indices.presentIndex.has_value() && this->select_indices.presentIndex != this->select_indices.graphicIndex){
        VkDeviceQueueCreateInfo present_q_info{};
        present_q_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        present_q_info.queueFamilyIndex = this->select_indices.presentIndex.value();
        present_q_info.queueCount = 1;
        present_q_info.pQueuePriorities = &queue_priority;
        queueCreateInfos.push_back(present_q_info);
    }

    if(this->select_indices.computeIndex.has_value() &&
       this->select_indices.computeIndex != this->select_indices.graphicIndex &&
       this->select_indices.computeIndex != this->select_indices.presentIndex 
    ){
        VkDeviceQueueCreateInfo compute_q_info{};
        compute_q_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        compute_q_info.queueFamilyIndex = this->select_indices.computeIndex.value();
        compute_q_info.queueCount = 1;
        compute_q_info.pQueuePriorities = &queue_priority;
        queueCreateInfos.push_back(compute_q_info);
    }


    uint32_t ext_count = 0;
    vkEnumerateDeviceExtensionProperties(this->physical_device, nullptr, &ext_count, nullptr);

    vector<VkExtensionProperties> extensions(ext_count);
    vkEnumerateDeviceExtensionProperties(this->physical_device, nullptr, &ext_count, extensions.data());
    vector<string> right_extensions(ext_count);
    for(const auto& ext : extensions ) right_extensions.push_back( string(ext.extensionName) ); 

    const char* req_ext[] = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    for(const char* ext : req_ext) {
        if(find(right_extensions.begin(), right_extensions.end(), string(ext) ) != right_extensions.end()) {
            this->extensions_device.push_back(ext);
        } else {
            ErrorNotiffication("Required extension not supported: ",file_name);
        }
    }

    bool hasKHR = false;
    bool hasEXT = false;
    for(const auto& ext : extensions){
        if( string(ext.extensionName) == VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME) hasKHR = true;
        if( string(ext.extensionName) == VK_EXT_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME) hasEXT = true;
    }
    
    if(hasKHR) this->extensions_device.push_back(VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME);
    else if(hasEXT) this->extensions_device.push_back(VK_EXT_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME);



    VkPhysicalDeviceFeatures device_f{};


    VkDeviceCreateInfo create_info {};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    create_info.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    create_info.pQueueCreateInfos = queueCreateInfos.data();
    create_info.enabledExtensionCount = static_cast<uint32_t>(this->extensions_device.size());
    create_info.ppEnabledExtensionNames = this->extensions_device.data();
    create_info.pEnabledFeatures = &device_f;

    check(
        vkCreateDevice(this->physical_device, &create_info, nullptr, &this->virtual_device),
        "Failed to create logical device"
    );

    
}


void Artifex::createQueue(){
    QFamily selected = getQueueFamilies(this->physical_device);
    this->graphics_index = selected.graphicIndex.value();
    this->present_index = selected.presentIndex.value();
    if(selected.computeIndex.has_value()) this->compute_index = selected.computeIndex.value();

    vkGetDeviceQueue(this->virtual_device, graphics_index, 0, &this->graphics_queue);
    vkGetDeviceQueue(this->virtual_device, present_index, 0, &this->present_queue);
    if(this->select_indices.computeIndex.has_value())
    vkGetDeviceQueue(this->virtual_device, compute_index, 0, &this->compute_queue);

}




void Artifex::destroyLogicalDevice(){
    if (virtual_device) vkDestroyDevice(virtual_device, nullptr);
}