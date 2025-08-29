#include "../../include/GPU.h"
#include "../../../pack.h"


void Artifex::createCommandPool(){

    auto check = [](VkResult obj,string error){
        if(obj != VK_SUCCESS){
            ErrorNotiffication(error.c_str(),__FILE__);
        }
    };

    VkCommandPoolCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    create_info.queueFamilyIndex = this->graphics_index;
    create_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    create_info.queueFamilyIndex = this->graphics_index;

    check(
        vkCreateCommandPool(this->virtual_device, &create_info, nullptr, &this->command_pool),
        "Failed to create command pool"
    );
}




void Artifex::destroyCommandPool(){
    if (command_pool) {
        vkDestroyCommandPool(virtual_device, command_pool, nullptr);
        command_pool = VK_NULL_HANDLE;
    }
}