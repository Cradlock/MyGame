#include "../../include/GPU.h"
#include "../../../pack.h"



void Artifex::createImageViews(){


    uint32_t imageCount = 0;
    vkGetSwapchainImagesKHR(this->virtual_device, this->swap_chain, &imageCount, nullptr);
    this->swap_chain_images.resize(imageCount);
    vkGetSwapchainImagesKHR(this->virtual_device, this->swap_chain, &imageCount, this->swap_chain_images.data());

    
    this->swap_chain_image_views.resize(this->swap_chain_images.size());
    for(size_t i = 0; i < this->swap_chain_images.size() ;++i){
        VkImageViewCreateInfo viewInfo{};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.image = swap_chain_images[i];
        viewInfo.format= this->swap_chain_format;
        viewInfo.components = { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY };
        viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        viewInfo.subresourceRange.levelCount = 1;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount = 1;

        vkCreateImageView(this->virtual_device, &viewInfo, nullptr, &swap_chain_image_views[i]);
    }


    this->depth_format = this->choiceDepthFormat();

    createImage(
        this->extent.width,
        this->extent.height,
        this->depth_format,
        VK_IMAGE_TILING_OPTIMAL,
        VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        this->depth_image,
        this->depth_image_memory
    );

    this->depth_image_view = createImageView(
        this->depth_image,
        this->depth_format,
        VK_IMAGE_ASPECT_DEPTH_BIT
    );

}





VkFormat Artifex::choiceDepthFormat(){
    vector<VkFormat> candidates = {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D24_UNORM_S8_UINT, VK_FORMAT_D32_SFLOAT_S8_UINT};
    VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
    VkFormatFeatureFlags features = VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT;

    for (VkFormat format : candidates) {
        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(physical_device, format, &props);

        if (tiling == VK_IMAGE_TILING_LINEAR &&
            (props.linearTilingFeatures & features) == features) {
            return format;
        } else if (tiling == VK_IMAGE_TILING_OPTIMAL &&
                   (props.optimalTilingFeatures & features) == features) {
            return format;
        }
    }

    ErrorNotiffication("No depth format", __FILE__);
    exit(EXIT_FAILURE);
   
}



void Artifex::createImage(uint32_t width,uint32_t height,VkFormat format,VkImageTiling tiling,VkImageUsageFlags usage,VkMemoryPropertyFlags properties,VkImage& image,VkDeviceMemory& imageMemory){
    VkImageCreateInfo create_info {};
    create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    create_info.imageType = VK_IMAGE_TYPE_2D;
    create_info.extent.width = width;
    create_info.extent.height = height;
    create_info.extent.depth = 1;
    create_info.mipLevels = 1;
    create_info.arrayLayers = 1;
    create_info.format = format;
    create_info.tiling = tiling;
    create_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    create_info.usage = usage;
    create_info.samples = VK_SAMPLE_COUNT_1_BIT;
    create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateImage(this->virtual_device, &create_info, nullptr, &image) != VK_SUCCESS) {
        ErrorNotiffication("Failed to create image!", __FILE__);
    }


    VkMemoryRequirements memReq;
    vkGetImageMemoryRequirements(this->virtual_device, image, &memReq);
    
    VkMemoryAllocateInfo info_loc{};
    info_loc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    info_loc.allocationSize = memReq.size;
    info_loc.memoryTypeIndex = this->findMemoryType(memReq.memoryTypeBits,properties);
    
    if(vkAllocateMemory(this->virtual_device, &info_loc, nullptr, &imageMemory) != VK_SUCCESS){
        ErrorNotiffication("Failed to allocate image memory", __FILE__);
    }

    vkBindImageMemory(this->virtual_device, image, imageMemory, 0);
}


uint32_t Artifex::findMemoryType(uint32_t filter,VkMemoryPropertyFlags props){
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(this->physical_device, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((filter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & props) == props) {
            return i;
        }
    }

    ErrorNotiffication("Failed to find suitable memory type!",__FILE__);
    exit(EXIT_FAILURE);
}


VkImageView Artifex::createImageView(VkImage img,VkFormat format,VkImageAspectFlags aspectFlags){

    VkImageViewCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    create_info.image = img;
    create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    create_info.format = format;
    create_info.subresourceRange.aspectMask = aspectFlags;
    create_info.subresourceRange.baseMipLevel = 0;
    create_info.subresourceRange.levelCount = 1;
    create_info.subresourceRange.baseArrayLayer = 0;
    create_info.subresourceRange.layerCount = 1;

    VkImageView imageView;
    if (vkCreateImageView(virtual_device, &create_info, nullptr, &imageView) != VK_SUCCESS) {
        ErrorNotiffication("Failed to create depth image view",__FILE__);

    }

    return imageView;
}




void Artifex::destroyImageViews(){
    for (auto view : swap_chain_image_views) {
        vkDestroyImageView(virtual_device, view, nullptr);
    }
    swap_chain_image_views.clear();
}


void Artifex::destroyDepthImage(){
    if (depth_image_view) vkDestroyImageView(virtual_device, depth_image_view, nullptr);
    if (depth_image) vkDestroyImage(virtual_device, depth_image, nullptr);
    if (depth_image_memory) vkFreeMemory(virtual_device, depth_image_memory, nullptr);
}