#include "../../include/GPU.h"
#include "../../../pack.h"



void Artifex::createFence(){
    auto check = [](VkResult obj,const std::string& error){
        if(obj != VK_SUCCESS){
            ErrorNotiffication(error.c_str(),__FILE__);
            return false;
        }
        return true;
    };


    this->fence.resize(MAX_FRAMES_IN_FLIGHT);   

    for(int i = 0 ; i < MAX_FRAMES_IN_FLIGHT ;++i){

    VkFenceCreateInfo create_info{};

    create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    create_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    if(check(
        vkCreateFence(this->virtual_device, &create_info, nullptr, &this->fence[i]),
        "Failed to create fence"
    ) != true){
        exit(EXIT_FAILURE);
    }

    }

    
}


void Artifex::destroyFence(){
    // if (fence) vkDestroyFence(virtual_device, fence, nullptr);
}