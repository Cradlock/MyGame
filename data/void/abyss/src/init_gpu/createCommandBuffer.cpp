#include "../../include/GPU.h"
#include "../../../pack.h"


void Artifex::createCommandBuffer(){

    auto check = [](VkResult obj,string error){
        if(obj != VK_SUCCESS){
            ErrorNotiffication(error.c_str(),__FILE__);
        }
    };
    
    
    this->command_buffer.resize(this->frame_buffer.size());

    VkCommandBufferAllocateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    create_info.commandPool = this->command_pool;
    create_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    create_info.commandBufferCount = (uint32_t) this->command_buffer.size();
    
    check(
        vkAllocateCommandBuffers(this->virtual_device, &create_info, this->command_buffer.data()),
        "Failed to allocate command buffer"
    );

}



void Artifex::destroyCommandBuffer(){
    if (!command_buffer.empty()) {
        vkFreeCommandBuffers(virtual_device, command_pool, command_buffer.size(), command_buffer.data());
        command_buffer.clear();
    }
}