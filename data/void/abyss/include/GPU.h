#pragma once

#ifndef UNICODE
#define UNICODE
#endif 

#include "Window.h"
#include "vulkan/vulkan.h"
#include <vulkan/vulkan_win32.h>
#include <vector>
#include <limits>
#include <algorithm>
#include <optional>
#include <fstream>
#include <array>





class Artifex{

public:
// новые типы данных
struct UniformBufferObject {
    float model[16];
    float view[16];
    float proj[16];
};

struct Vertex{
    float pos[3];
    float color[3];

    static VkVertexInputBindingDescription getBindDesc(){
        VkVertexInputBindingDescription res{};
        res.binding = 0;
        res.stride = sizeof(Vertex);
        res.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return res;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttrDesc(){
        std::array<VkVertexInputAttributeDescription,2> res{};
        
        // pos -> layout(location = 0)
        res[0].binding = 0;
        res[0].location = 0;
        res[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        res[0].offset = offsetof(Vertex, pos);
        
        // color -> layout(location = 1)
        res[1].binding = 0;
        res[1].location = 1;
        res[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        res[1].offset = offsetof(Vertex, color);

        return res;
    } 
};


struct QFamily {
    std::optional<uint32_t> graphicIndex;
    std::optional<uint32_t> presentIndex;
    std::optional<uint32_t> computeIndex;

    bool isOwnComplete() const {
        return graphicIndex.has_value() && presentIndex.has_value() && computeIndex.has_value();
    }

    bool isComplete() const {
        return graphicIndex.has_value() && presentIndex.has_value();
    }

};


// Аттрибуты для отрисовки
std::vector<Vertex> targets;


// Память под отрисовку

VkBuffer staging_buffer;
VkDeviceMemory staging_memory;

VkBuffer vertex_buffer;
VkDeviceMemory vertex_memory;

VkBuffer index_buffer;
VkDeviceMemory index_memory;

VkBuffer uniform_buffer;
VkDeviceMemory uniform_memory;



private:
// Окно программы
PanarchonWindow* window = nullptr;


// Сама программа    
VkInstance instance;

// Расширения для Vulkan программы
vector<VkExtensionProperties> extensions_instance;

// Поверхность рисования 
VkSurfaceKHR surface;

// физическое устройство
VkPhysicalDevice physical_device;

// Выбранные очереди
QFamily select_indices;

// Включенные расширения в работу лог-устройства
vector<const char*> extensions_device;

// Логическое устройство
VkDevice virtual_device; 

// Очереди
VkQueue graphics_queue;  
uint32_t graphics_index;

VkQueue present_queue; 
uint32_t present_index;  

VkQueue compute_queue; 
uint32_t compute_index;  

// Командный пул
VkCommandPool command_pool;

// Размер экрана
VkExtent2D extent; 

// Формат цветового пространства
VkSurfaceFormatKHR format;  

// Режим обновление кадров
VkPresentModeKHR present_mode;

// Swap Chain
VkSwapchainKHR swap_chain;

// Изображения для отрисовки
vector<VkImage> swap_chain_images;

// Представление изображений
vector<VkImageView> swap_chain_image_views;

// Формат для глубины изображений
VkFormat depth_format;

//Картинка для эффекта глубины
VkImage depth_image;

//Память для картины depth_image
VkDeviceMemory depth_image_memory;

//Представление depth_image
VkImageView depth_image_view;  

// Цветовой формат для Swap Chain
VkFormat swap_chain_format;

//Настройка рендеринга
VkRenderPass render_pass;
   // цветовое прикрепление
   VkAttachmentReference colorAttachmentRef;
   // глубинное прикрепление
   VkAttachmentReference depthAttachmentRef;    

//Шейдерные модули
VkShaderModule frag_shader;
VkShaderModule vert_shader;

// настройки для дескриптора 
VkDescriptorSetLayout descriptor_set_layout;

//Каркас графического конвейера
VkPipelineLayout pipeline_layout;  

//Графический конвейер
VkPipeline graphic_conv;   

// буфер кадров
vector<VkFramebuffer> frame_buffer;

//буфер команд
vector<VkCommandBuffer> command_buffer;



//Семафоры
  int MAX_FRAMES_IN_FLIGHT;
vector<VkSemaphore> imgAvailableSemaphore;
vector<VkSemaphore> renderFinishedSemaphore;

//Барьер
vector<VkFence> fence;   
   
// Дескрипторы
   // буферы для unform(шейдеров)
   vector<VkBuffer> uniform_buffers;
   vector<VkDeviceMemory> uniform_buffers_memory;

   // Пул для дескриптора шейдеров
   VkDescriptorPool descriptor_pool;

   // Дескрипторы   
   vector<VkDescriptorSet> descriptor_set;  
   
// Текущий кадр
uint32_t current_frame; 

public:

Artifex(PanarchonWindow& wind);

// инициализация
void init();
    void createInstance(); //
    void createSurface();
    void choicePhysicalDevice();
    void createLogicalDevice();
    // реализовано в init_gpu/createLogicalDevice.cpp
    void createQueue();
    void createCommandPool();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createDescriptorSetLayout();
    void createGraphicPipeline();
    void createFrameBuffer();
    void createCommandBuffer();
    void createSemaphore();
    void createFence();
    // реализовано в init_gpu/createDescriptors.cpp
    void create_DescriptorPool();
    void create_UniformBuffer();
    void create_DescriptorSet();

// Уничтожение
void destroy();
    void destroyCommandBuffer();
    void destroyCommandPool();
    void destroyFrameBuffer();
    void destroyImageViews();
    void destroySwapChain();
    void destroyDepthImage();
    void destroyGraphicPipeline();
    void destroyPipelineLayout();
    void destroyShaders();
    void destroyRenderPass();
    void destroySemaphore();
    void destroyFence();
    void destroyLogicalDevice();
    void destroySurface();
    void destroyInstance();




// Дополнительные функции

// Реализовано в init_gpu/choicePhysicalDevice.cpp
QFamily getQueueFamilies(VkPhysicalDevice device);


// Реализовано в init_gpu/createSwapChain.cpp
VkSurfaceFormatKHR chooseSurfaceFormat(vector<VkSurfaceFormatKHR>& formats );

// Реализовано в init_gpu/createSwapChain.cpp
VkPresentModeKHR choosePresentMode(vector<VkPresentModeKHR>& modes );

// Реализовано в init_gpu/createSwapChain.cpp
VkExtent2D chooseExtent(const VkSurfaceCapabilitiesKHR& capabilities);

// Реализовано в createImageVIews.cpp 
VkFormat choiceDepthFormat();

// Реализовано в createImageVIews.cpp 
void createImage(uint32_t width,uint32_t height,VkFormat format,VkImageTiling tiling,VkImageUsageFlags usage,VkMemoryPropertyFlags properties,VkImage& image,VkDeviceMemory& imageMemory);

// Реализовано в createImageVIews.cpp 
uint32_t findMemoryType(uint32_t filter,VkMemoryPropertyFlags props);

// Реализовано в createImageVIews.cpp 
VkImageView createImageView(VkImage img,VkFormat format,VkImageAspectFlags aspectFlags);

// Реализовано в init_gpu/createRenderPass.cpp
VkAttachmentDescription colorAttachment();

// Реализовано в init_gpu/createRenderPass.cpp
VkAttachmentDescription depthAttachment();

// Реализовано в init_gpu/createRenderPass.cpp
void set_colorAttachmentRef();

// Реализовано в init_gpu/createRenderPass.cpp
void set_depthAttachmentRef();

// Реализовано в init_gpu/createRenderPass.cpp
VkSubpassDescription create_subpass();


// Отдельная секция для опредления графического конвейера

// Реализовано в init_gpu/createRenderPass.cpp
   vector<char> read_shader(string path);

   VkShaderModule create_ShaderModule(const vector<char>& code);
   
   VkPipelineShaderStageCreateInfo create_VertShaderStage();
   
   VkPipelineShaderStageCreateInfo create_FragShaderStage();

   VkPipelineVertexInputStateCreateInfo create_VertexInput();

   VkPipelineInputAssemblyStateCreateInfo create_InputAssembly();

   VkPipelineRasterizationStateCreateInfo create_Rasterizer();

   VkPipelineMultisampleStateCreateInfo create_Multisampling();

   VkPipelineDepthStencilStateCreateInfo create_DepthStencil();
   
   VkPipelineLayoutCreateInfo create_PipelineLayout();

   VkPipelineDynamicStateCreateInfo create_DynamicState();


//Функции для отрисовки



void update();
   uint32_t takeFrame();

   void drawFrame(uint32_t img_index);



   void presentFrame(uint32_t img_index);
   


// Функции для работы с паматью

void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory);

void createStagingBuffer();

void createVertexBuffer();

void createUniformBuffer();

void recordCmdBuffer(VkCommandBuffer buffer,uint32_t img_index);

void sendQueue(uint32_t img_index);

VkCommandBuffer beginSingleTimeCommands();

void endSingleTimeCommands(VkCommandBuffer command_buffer);

};


