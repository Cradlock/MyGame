#include "../../include/GPU.h"
#include "../../../pack.h"


void Artifex::presentFrame(uint32_t img_index){

    VkSemaphore signalSem = renderFinishedSemaphore[img_index];
    
    VkPresentInfoKHR present{};
    present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    VkSemaphore waitSemaphores[] = { signalSem };
    present.waitSemaphoreCount = 1;
    present.pWaitSemaphores = waitSemaphores;
    
    present.swapchainCount = 1;
    present.pSwapchains = &this->swap_chain;
    present.pImageIndices = &img_index;

    vkQueuePresentKHR(this->present_queue, &present);

    current_frame = (current_frame + 1) % MAX_FRAMES_IN_FLIGHT;
}

