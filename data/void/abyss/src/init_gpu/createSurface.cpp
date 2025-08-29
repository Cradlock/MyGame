#include "../../include/GPU.h"
#include "../../../pack.h"


void Artifex::createSurface(){
    string file_name = "abyss/src/init_gpu/createSurface.cpp";

    auto check = [file_name](VkResult obj,string error){
        if(obj != VK_SUCCESS){
            ErrorNotiffication(error.c_str(),file_name);
        }
    };

#ifdef _WIN32
    
    VkWin32SurfaceCreateInfoKHR create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    create_info.hinstance = this->window->gethInstance();
    create_info.hwnd = this->window->getMainWindow();

    check(
        vkCreateWin32SurfaceKHR(this->instance, &create_info, nullptr, &surface),
        "Failed to create Win32 surface"
    );

#else 

   #error "Platform not suporrted"

#endif 

}




void Artifex::destroySurface(){
    if (this->surface != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(this->instance, this->surface, nullptr);
        this->surface = VK_NULL_HANDLE;
    }
}