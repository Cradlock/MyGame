#include "../include/GPU.h"
#include "../../pack.h"

#ifndef UNICODE
#define UNICODE
#endif 


void Artifex::createStagingBuffer(){
    VkDeviceSize vertexSize = sizeof(targets[0]) * targets.size();
    
    
    createBuffer(
        vertexSize,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        this->staging_buffer,
        this->staging_memory
    );

    void* data;
    vkMapMemory(this->virtual_device, this->staging_memory, 0, vertexSize, 0, &data);
    memcpy(data, targets.data(), (size_t)vertexSize);
    vkUnmapMemory(this->virtual_device, this->staging_memory);
}

void Artifex::createVertexBuffer(){
 VkDeviceSize vertexSize = sizeof(targets[0]) * targets.size();

    // Создание device local vertex buffer
    createBuffer(
        vertexSize,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        this->vertex_buffer,
        this->vertex_memory
    );

    // Копирование данных из staging buffer
    VkCommandBuffer commandBuffer = beginSingleTimeCommands(); // утилита для одноразового cmd buffer
    VkBufferCopy copyRegion{};
    copyRegion.srcOffset = 0;
    copyRegion.dstOffset = 0;
    copyRegion.size = vertexSize;
    vkCmdCopyBuffer(commandBuffer, this->staging_buffer, this->vertex_buffer, 1, &copyRegion);
    endSingleTimeCommands(commandBuffer);

};

void Artifex::createUniformBuffer(){
    // uniform buffer
    VkDeviceSize uboSize = sizeof(Artifex::UniformBufferObject);
    this->uniform_buffers.resize(MAX_FRAMES_IN_FLIGHT);
    this->uniform_buffers_memory.resize(MAX_FRAMES_IN_FLIGHT);

    for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT ;++i){
       createBuffer(
        uboSize,
        VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        this->uniform_buffers[i],
        this->uniform_buffers_memory[i]
       );
    }

}


void Artifex::recordCmdBuffer(VkCommandBuffer buffer,uint32_t img_index){
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0;

    vkBeginCommandBuffer(buffer, &beginInfo);
    
    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = this->render_pass;
    renderPassInfo.framebuffer = this->frame_buffer[img_index];
    renderPassInfo.renderArea.offset = {0,0};
    renderPassInfo.renderArea.extent = this->extent;

    VkClearValue clearValues[2];
    clearValues[0].color = {{0.0f,0.0f,0.0f,0.1f}};
    clearValues[1].depthStencil = {1.0f,0};

    renderPassInfo.clearValueCount = 2;
    renderPassInfo.pClearValues = clearValues;

    vkCmdBeginRenderPass(buffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(buffer,VK_PIPELINE_BIND_POINT_GRAPHICS,this->graphic_conv);

    VkBuffer vertexBuffer[] = {  this->vertex_buffer };
    VkDeviceSize offsets[] = { 0 };
    
    vkCmdBindDescriptorSets(
        buffer,
        VK_PIPELINE_BIND_POINT_GRAPHICS,
        this->pipeline_layout,
        0,
        1,
        this->descriptor_set.data(),
        0,
        nullptr
    );


    vkCmdBindVertexBuffers(
        buffer, 
        0, 
        1, 
        vertexBuffer, 
        offsets
    );

    vkCmdDraw(buffer,static_cast<uint32_t>(targets.size()),1, 0, 0);

    vkCmdEndRenderPass(buffer);

    vkEndCommandBuffer(buffer);
}


void Artifex::sendQueue(uint32_t img_index){
    VkSemaphore waitSem = imgAvailableSemaphore[current_frame];

    VkSemaphore signalSem = renderFinishedSemaphore[current_frame];

    if (waitSem == VK_NULL_HANDLE || signalSem == VK_NULL_HANDLE) {
    std::cerr << "Error: Semaphore invalid for current_frame = " << current_frame << std::endl;
    return;
}
    
    VkSubmitInfo submit{};
    submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    
    VkSemaphore waitSemaphores[] = { waitSem };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    
    submit.waitSemaphoreCount = 1;
    submit.pWaitSemaphores = waitSemaphores;
    submit.pWaitDstStageMask = waitStages;
    
    submit.commandBufferCount = 1;
    submit.pCommandBuffers = &command_buffer[img_index];
    
    VkSemaphore signalSemaphores[] = { signalSem };
    submit.signalSemaphoreCount = 1;
    submit.pSignalSemaphores = signalSemaphores;

    vkResetFences(this->virtual_device, 1, &fence[current_frame]);
    vkQueueSubmit(this->graphics_queue, 1, &submit, this->fence[current_frame]);

}

void Artifex::presentFrame(uint32_t img_index){
    VkPresentInfoKHR present{};

    VkSemaphore signalSem = renderFinishedSemaphore[current_frame];

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


VkCommandBuffer Artifex::beginSingleTimeCommands(){
    // Аллокация командного буфера
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = this->command_pool;  // твой пул команд
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(this->virtual_device, &allocInfo, &commandBuffer);

    // Начало записи команд
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT; // одноразовый буфер!

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}


void Artifex::endSingleTimeCommands(VkCommandBuffer commandBuffer){
    vkEndCommandBuffer(commandBuffer);

    // Отправка в графическую очередь
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(this->graphics_queue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(this->graphics_queue); // ждем, пока GPU выполнит

    // Освобождаем командный буфер
    vkFreeCommandBuffers(this->virtual_device, this->command_pool, 1, &commandBuffer);
}


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

uint32_t Artifex::takeFrame(){
    vkWaitForFences(this->virtual_device,1,&fence[current_frame], VK_TRUE,UINT64_MAX);
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
        return -1;
    }else if(res != VK_SUCCESS){
        ErrorNotiffication("Failed to get a frame",__FILE__);    
        return -1;
    }
  
    return image_index;
}

void Artifex::drawFrame(uint32_t img_index){

   this->recordCmdBuffer(this->command_buffer[img_index], img_index);
   this->sendQueue(img_index);
   
}



