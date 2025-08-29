#include "../../include/GPU.h"
#include "../../../pack.h"


void Artifex::createSemaphore(){
    this->MAX_FRAMES_IN_FLIGHT = std::min<size_t>(2, this->swap_chain_images.size());

    
    auto check = [](VkResult obj,const std::string& error){
        if(obj != VK_SUCCESS){
            ErrorNotiffication(error.c_str(),__FILE__);
            return false;
        }
        return true;
    };
    
    this->imgAvailableSemaphore.resize(this->swap_chain_images.size());
    this->renderFinishedSemaphore.resize(this->swap_chain_images.size());

    VkSemaphoreCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    create_info.flags = 0;
    
    
    for(int i = 0; i < this->swap_chain_images.size(); ++i){
        if(!check(
                vkCreateSemaphore(this->virtual_device, &create_info, nullptr, &this->imgAvailableSemaphore[i]),
                "Failed to create semaphore in imgAvailable (cycle):"+std::to_string(i)) ||
           !check(vkCreateSemaphore(this->virtual_device, &create_info, nullptr, &this->renderFinishedSemaphore[i]),
                  "Failed to create semaphore in renderFinished (cycle):"+std::to_string(i)))
        {
            ErrorNotiffication("Failed to create semaphores",__FILE__);
            exit(EXIT_FAILURE);
        }
    }
    
}




void Artifex::destroySemaphore(){
    for (auto sem : imgAvailableSemaphore) vkDestroySemaphore(virtual_device, sem, nullptr);
    for (auto sem : renderFinishedSemaphore) vkDestroySemaphore(virtual_device, sem, nullptr);
    imgAvailableSemaphore.clear();
    renderFinishedSemaphore.clear();
}