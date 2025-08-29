#include "../../include/GPU.h"
#include "../../../pack.h"


void Artifex::createFrameBuffer(){
    string file_name = "abyss/src/init_gpu/createFrameBuffer.cpp";

    auto check = [file_name](VkResult obj,string error){
        if(obj != VK_SUCCESS){
            ErrorNotiffication(error.c_str(),file_name);
        }
    };
    
    size_t img_count = this->swap_chain_image_views.size();
    this->frame_buffer.resize(img_count);

    for(size_t i = 0; i < img_count ;++i){  
        array<VkImageView, 2> attachments = {
            swap_chain_image_views[i],  
            depth_image_view            
        };


        VkFramebufferCreateInfo framebuffer_info{};
        framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebuffer_info.renderPass = this->render_pass;
        framebuffer_info.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebuffer_info.pAttachments = attachments.data();
        framebuffer_info.width  = this->extent.width;
        framebuffer_info.height = this->extent.height;
        framebuffer_info.layers = 1;


        VkResult result = vkCreateFramebuffer(
            this->virtual_device,
            &framebuffer_info,
            nullptr,
            &this->frame_buffer[i]
        );

        check(
            result, 
            "Failed to create Framebuffer"
        );

    }

    
}



void Artifex::destroyFrameBuffer(){
    for (auto fb : frame_buffer) {
        vkDestroyFramebuffer(virtual_device, fb, nullptr);
    }
    frame_buffer.clear();
}