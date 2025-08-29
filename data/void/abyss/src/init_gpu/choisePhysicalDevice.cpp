#include "../../include/GPU.h"
#include "../../../pack.h"


Artifex::QFamily Artifex::getQueueFamilies(VkPhysicalDevice device){
    Artifex::QFamily indices;

    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);

    vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());
    
    for(uint32_t i = 0; i < queue_family_count ;++i){
        const auto& queueFamily = queue_families[i];

        if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT ){
            indices.graphicIndex = i;
        }


        if(queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT ){
            indices.computeIndex = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i,this->surface, &presentSupport);
        if(presentSupport) {
            indices.presentIndex = i;
        }
        
        if(indices.isOwnComplete()) break;

        if(indices.isComplete()) break;
    }
    
    return indices;
}


void Artifex::choicePhysicalDevice(){
    string file_name = "abyss/src/init_gpu/choicePhysicalDevice.cpp";

    auto check = [file_name](VkResult obj,string error){
        if(obj != VK_SUCCESS){
            ErrorNotiffication(error.c_str(),file_name);
        }
    };

    auto check_zero = [file_name](int obj,string error){
        if(obj == 0){
            ErrorNotiffication(error.c_str(),file_name);
        }
    };

    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(this->instance, &device_count, nullptr);
    check_zero(device_count,"No Vulkan-compatible GPUs found!");


    vector<VkPhysicalDevice> devices(device_count);
    vkEnumeratePhysicalDevices(this->instance,&device_count,devices.data());
    
    vector<VkPhysicalDevice> right_devices;

    for(const auto& device : devices){
        Artifex::QFamily indices = getQueueFamilies(device);
        

        if(indices.isOwnComplete()){
            right_devices.push_back(device);
            continue;
        }

        if(indices.isComplete()){
            right_devices.push_back(device);
        }

    }

    if (right_devices.empty()) {
       ErrorNotiffication("No suitable GPU found", file_name);
       exit(EXIT_FAILURE);
    }
    
    VkPhysicalDevice best_device = right_devices[0];
    int best_score = 0;
    for(const auto& device : right_devices){
        Artifex::QFamily indices = getQueueFamilies(device);

        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(device,&props);

        int score = 0;
        if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            score += 3000;
        }

        if (indices.isOwnComplete()) score += 1000;
        score += props.limits.maxImageDimension2D;
        score += props.limits.maxComputeWorkGroupInvocations;

        if(score > best_score){
            best_score = score;
            best_device = device;
            this->select_indices = indices;
        }
    }
    
    
    this->physical_device = best_device;
     
}