#include "../include/GPU.h"
#include "../../pack.h"

#ifndef UNICODE
#define UNICODE
#endif 








Artifex::Artifex(PanarchonWindow& wind) 
: physical_device(VK_NULL_HANDLE),window(&wind),current_frame(0)
{
  
    createInstance();
    createSurface();
    choicePhysicalDevice();
    createLogicalDevice();
    createQueue();
    createCommandPool();
    createSwapChain();
    createImageViews();
    createRenderPass();
    createDescriptorSetLayout();
    createGraphicPipeline();
    createFrameBuffer();
    createCommandBuffer();
    createSemaphore();
    createFence();
    create_UniformBuffer();
    create_DescriptorPool();
    create_DescriptorSet();

}
 
void Artifex::destroy(){
    destroyCommandBuffer();
    destroyCommandPool();
    destroyFrameBuffer();
    destroyImageViews();
    destroySwapChain();
    destroyDepthImage();
    destroyGraphicPipeline();
    destroyPipelineLayout();
    destroyShaders();
    destroyRenderPass();
    destroySemaphore();
    destroyFence();
    destroyLogicalDevice();
    destroySurface();
    destroyInstance();

}







void Artifex::update(){
    uint32_t img_index = this->takeFrame();
    this->drawFrame(img_index);
    this->presentFrame(img_index);
}

void Artifex::drawFrame(uint32_t img_index){

   this->recordCmdBuffer(this->command_buffer[img_index], img_index);
   this->sendQueue(img_index);
   
}





