#include "../../include/GPU.h"
#include "../../../pack.h"



void Artifex::createDescriptorSetLayout(){
    VkDescriptorSetLayoutBinding ubo_info{};
    ubo_info.binding = 0;
    ubo_info.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    ubo_info.descriptorCount = 1;
    ubo_info.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    ubo_info.pImmutableSamplers = nullptr; 


    VkDescriptorSetLayoutCreateInfo layout_info{};
    layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layout_info.bindingCount = 1;               
    layout_info.pBindings = &ubo_info;
    
    if(vkCreateDescriptorSetLayout(this->virtual_device, &layout_info, nullptr, &this->descriptor_set_layout) != VK_SUCCESS){
        ErrorNotiffication("FAILED to create descriptor set layout",__FILE__);
    }   
    
}