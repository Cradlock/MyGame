#include "../../include/GPU.h"
#include "../../../pack.h"


uint32_t Artifex::takeFrame()   {
    
    vkWaitForFences(this->virtual_device, 1, &fence[current_frame], VK_TRUE, UINT64_MAX);
    vkResetFences(this->virtual_device, 1, &fence[current_frame]);

    uint32_t image_index = 0;
    VkResult res = vkAcquireNextImageKHR(
        this->virtual_device,
        this->swap_chain,
        UINT64_MAX,
        this->imgAvailableSemaphore[current_frame], 
        VK_NULL_HANDLE,
        &image_index
    );

    if(res == VK_ERROR_OUT_OF_DATE_KHR ){
        ErrorNotiffication("Write new function for recreate SwapChain",__FILE__);
        return UINT32_MAX;
    } else if(res != VK_SUCCESS && res != VK_SUBOPTIMAL_KHR){
        ErrorNotiffication("Failed to get a frame",__FILE__);    
        return UINT32_MAX;
    }

    if (imagesInFlight[image_index] != VK_NULL_HANDLE) {
        vkWaitForFences(this->virtual_device, 1, &imagesInFlight[image_index], VK_TRUE, UINT64_MAX);
    }

    imagesInFlight[image_index] = fence[current_frame];

    return image_index;
}