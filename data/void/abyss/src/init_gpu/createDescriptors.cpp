#include "../../include/GPU.h"
#include "../../../pack.h"


void Artifex::createBuffer
(
    VkDeviceSize size, 
    VkBufferUsageFlags usage, 
    VkMemoryPropertyFlags properties, 
    VkBuffer &buffer, 
    VkDeviceMemory &bufferMemory
){
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(virtual_device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        ErrorNotiffication("failed to create buffer!",__FILE__);
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(virtual_device, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(virtual_device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        ErrorNotiffication("failed to allocate buffer memory!",__FILE__);
    }

    vkBindBufferMemory(virtual_device, buffer, bufferMemory, 0);
}

void Artifex::create_DescriptorPool(){
    VkDescriptorPoolSize pool_size{};
    pool_size.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    pool_size.descriptorCount = static_cast<uint32_t>(this->MAX_FRAMES_IN_FLIGHT);

    VkDescriptorPoolCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    create_info.poolSizeCount = 1;
    create_info.pPoolSizes = &pool_size;
    create_info.maxSets = static_cast<uint32_t>(this->MAX_FRAMES_IN_FLIGHT);

    if(vkCreateDescriptorPool(this->virtual_device, &create_info, nullptr,&this->descriptor_pool)  != VK_SUCCESS){
        ErrorNotiffication("Failed to create decsriptor pool",__FILE__);
    }

}

void Artifex::create_UniformBuffer(){
    VkDeviceSize bufferSize = sizeof(Artifex::UniformBufferObject); 

    uniform_buffers.resize(MAX_FRAMES_IN_FLIGHT);
    uniform_buffers_memory.resize(MAX_FRAMES_IN_FLIGHT);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        createBuffer(
            bufferSize,
            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            uniform_buffers[i],
            uniform_buffers_memory[i]
        );
    }   

}


void Artifex::create_DescriptorSet(){
    std::vector<VkDescriptorSetLayout> layouts(static_cast<size_t>(this->MAX_FRAMES_IN_FLIGHT), this->descriptor_set_layout);

    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = this->descriptor_pool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
    allocInfo.pSetLayouts = layouts.data();

    this->descriptor_set.resize(MAX_FRAMES_IN_FLIGHT);

    if(vkAllocateDescriptorSets(this->virtual_device, &allocInfo, this->descriptor_set.data() ) != VK_SUCCESS){
        ErrorNotiffication("Failed to allocat for descriptos set",__FILE__);
    }

    for(size_t i = 0;i < MAX_FRAMES_IN_FLIGHT; ++i){
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = uniform_buffers[i];        
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);
    
        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = descriptor_set[i];  
        descriptorWrite.dstBinding = 0;               
        descriptorWrite.dstArrayElement = 0;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pBufferInfo = &bufferInfo;   
        descriptorWrite.pImageInfo = nullptr;         
        descriptorWrite.pTexelBufferView = nullptr;

        vkUpdateDescriptorSets(this->virtual_device, 1, &descriptorWrite, 0, nullptr);
    }


    

}