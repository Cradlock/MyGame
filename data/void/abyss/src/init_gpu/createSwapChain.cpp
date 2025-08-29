#include "../../include/GPU.h"
#include "../../../pack.h"


VkSurfaceFormatKHR Artifex::chooseSurfaceFormat(vector<VkSurfaceFormatKHR>& formats){
    for(const auto& format : formats){
        if(format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return format;
        }
    }
    return formats[0];
}

VkPresentModeKHR Artifex::choosePresentMode(vector<VkPresentModeKHR>& modes){
    for (const auto& mode : modes) {
        if (mode == VK_PRESENT_MODE_MAILBOX_KHR) return mode;
    }
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D Artifex::chooseExtent(const VkSurfaceCapabilitiesKHR& capabilities){
    if(capabilities.currentExtent.width != UINT32_MAX){
        return capabilities.currentExtent;
    } else {
        auto [width,height] = window->getSizeWindow();
        VkExtent2D actualExtent = {
            clamp<uint32_t>(width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width),
            clamp<uint32_t>(height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height)
        };
        return actualExtent;
    }
}

void Artifex::createSwapChain(){
    string file_name = "abyss/src/init_gpu/createSwapChain.cpp";

    auto check = [file_name](VkResult obj,string error){
        if(obj != VK_SUCCESS){
            ErrorNotiffication(error.c_str(),file_name);
        }
    };

    VkSurfaceCapabilitiesKHR surface_capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(this->physical_device, this->surface, &surface_capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(this->physical_device,this->surface, &formatCount, nullptr);
    vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(this->physical_device,this->surface, &formatCount, surfaceFormats.data());

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(this->physical_device,this->surface,&presentModeCount, nullptr);
    vector<VkPresentModeKHR> presentModes(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(this->physical_device,this->surface,&presentModeCount, presentModes.data());

    
    this->extent = this->chooseExtent(surface_capabilities);
    this->format = this->chooseSurfaceFormat(surfaceFormats);
    this->present_mode = this->choosePresentMode(presentModes);
    
    
    uint32_t imageCount = surface_capabilities.minImageCount + 1;
    if( surface_capabilities.maxImageCount > 0 && imageCount > surface_capabilities.maxImageCount ){
        imageCount = surface_capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    create_info.surface = this->surface;

    create_info.minImageCount = imageCount;
    create_info.imageFormat = this->format.format;
    create_info.imageColorSpace = this->format.colorSpace;
    create_info.imageExtent = this->extent;
    create_info.imageArrayLayers = 1;
    create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    uint32_t q_family_indices[] = {
        this->select_indices.graphicIndex.value(),
        this->select_indices.presentIndex.value()
    };

    if(this->select_indices.graphicIndex != this->select_indices.presentIndex){
        create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        create_info.queueFamilyIndexCount = 2;
        create_info.pQueueFamilyIndices = q_family_indices;
    } else {
        create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }

    create_info.preTransform = surface_capabilities.currentTransform;
    create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    create_info.presentMode = this->present_mode;
    create_info.clipped = VK_TRUE;
    create_info.oldSwapchain = VK_NULL_HANDLE;

    check(
        vkCreateSwapchainKHR(this->virtual_device,&create_info, nullptr, &this->swap_chain),
        "Failed to create swap chain"
    );
    
    this->swap_chain_format = this->format.format;

}



void Artifex::destroySwapChain(){
    if (swap_chain) {
        vkDestroySwapchainKHR(virtual_device, swap_chain, nullptr);
        swap_chain = VK_NULL_HANDLE;
    }

}