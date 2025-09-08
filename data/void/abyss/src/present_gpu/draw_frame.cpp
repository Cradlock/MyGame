#include "../../include/GPU.h"
#include "../../../pack.h"



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

    vkCmdBindIndexBuffer(
        buffer, 
        this->index_buffer, 
        0, 
        VK_INDEX_TYPE_UINT16
    );

    vkCmdDrawIndexed(buffer,static_cast<uint32_t>(indices.size()),1, 0, 0, 0);

    vkCmdEndRenderPass(buffer);

    vkEndCommandBuffer(buffer);
}




void Artifex::sendQueue(uint32_t img_index){
    VkSemaphore waitSem = imgAvailableSemaphore[current_frame];

    VkSemaphore signalSem = renderFinishedSemaphore[img_index];

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