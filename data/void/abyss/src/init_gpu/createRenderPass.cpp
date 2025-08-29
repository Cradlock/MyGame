#include "../../include/GPU.h"
#include "../../../pack.h"

void Artifex::createRenderPass(){
    string file_name = "abyss/src/init_gpu/createRenderPass.cpp";

    auto check = [file_name](VkResult obj,string error){
        if(obj != VK_SUCCESS){
            ErrorNotiffication(error.c_str(),file_name);
        }
    };
    
    VkAttachmentDescription colorAtt = this->colorAttachment();
    VkAttachmentDescription depthAtt = this->depthAttachment();
    VkSubpassDescription subpass = create_subpass();

    array<VkAttachmentDescription, 2> attachments = { colorAtt,depthAtt };
    
    VkRenderPassCreateInfo create_info {};
    create_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    create_info.attachmentCount = static_cast<uint32_t>(attachments.size());
    create_info.pAttachments = attachments.data();
    create_info.subpassCount = 1;
    create_info.pSubpasses = &subpass; 

    check(
        vkCreateRenderPass(this->virtual_device, &create_info, nullptr, &this->render_pass),
        "Failed to create render pass"
    );
    
}



VkAttachmentDescription Artifex::colorAttachment(){
   VkAttachmentDescription color_at {};
   color_at.format = this->swap_chain_format;
   color_at.samples = VK_SAMPLE_COUNT_1_BIT;
   color_at.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
   color_at.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
   color_at.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
   color_at.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

   color_at.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

   color_at.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

   return color_at;

}

VkAttachmentDescription Artifex::depthAttachment(){
   VkAttachmentDescription depth_at{};
   depth_at.format = this->depth_format;
   depth_at.samples = VK_SAMPLE_COUNT_1_BIT;
   depth_at.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
   depth_at.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
   depth_at.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
   depth_at.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
   depth_at.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
   depth_at.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

   return depth_at;
}



void Artifex::set_colorAttachmentRef(){
   VkAttachmentReference color_at_ref{};
   color_at_ref.attachment = 0;
   color_at_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
   this->colorAttachmentRef = color_at_ref;
}

void Artifex::set_depthAttachmentRef(){
   VkAttachmentReference depth_at_ref{};
   depth_at_ref.attachment = 1;
   depth_at_ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
   this->depthAttachmentRef = depth_at_ref;
}

VkSubpassDescription Artifex::create_subpass(){
    this->set_colorAttachmentRef();
    this->set_depthAttachmentRef();

    VkSubpassDescription subpass{};
    
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &this->colorAttachmentRef;
    subpass.pDepthStencilAttachment = &depthAttachmentRef;
    return subpass; 
}




void Artifex::destroyRenderPass(){
    if (render_pass) vkDestroyRenderPass(virtual_device, render_pass, nullptr);
}