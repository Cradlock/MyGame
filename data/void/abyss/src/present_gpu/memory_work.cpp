#include "../../include/GPU.h"
#include "../../../pack.h"


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



void Artifex::createIndexBuffer() {
    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

    // 🔹 staging buffer для загрузки данных
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingMemory;

    createBuffer(
        bufferSize,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        stagingBuffer,
        stagingMemory
    );

    void* data;
    vkMapMemory(this->virtual_device, stagingMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t) bufferSize);
    vkUnmapMemory(this->virtual_device, stagingMemory);

    // 🔹 device local index buffer
    createBuffer(
        bufferSize,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        this->index_buffer,
        this->index_memory
    );

    // 🔹 копирование staging → index_buffer
    VkCommandBuffer commandBuffer = beginSingleTimeCommands();
    VkBufferCopy copyRegion{};
    copyRegion.size = bufferSize;
    vkCmdCopyBuffer(commandBuffer, stagingBuffer, this->index_buffer, 1, &copyRegion);
    endSingleTimeCommands(commandBuffer);

    // 🔹 чистим staging (он больше не нужен)
    vkDestroyBuffer(this->virtual_device, stagingBuffer, nullptr);
    vkFreeMemory(this->virtual_device, stagingMemory, nullptr);
}