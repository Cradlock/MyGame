#include "../../include/GPU.h"
#include "../../../pack.h"



void Artifex::createGraphicPipeline(){
    string file_name = "abyss/src/init_gpu/createGraphicPipeline.cpp";
    auto check = [file_name](VkResult obj,string error){
        if(obj != VK_SUCCESS){
            ErrorNotiffication(error.c_str(),file_name);
        }
    };
    
    auto vertStage = this->create_VertShaderStage();
    auto fragStage = this->create_FragShaderStage();
    VkPipelineShaderStageCreateInfo shaderStages[] = {vertStage, fragStage};

    auto vertexInput  = this->create_VertexInput();
    auto inputAssembly= this->create_InputAssembly();
    
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width  = (float)this->extent.width;
    viewport.height = (float)this->extent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    
    VkRect2D scissor{};
    scissor.offset = {0,0};
    scissor.extent = this->extent;
    
    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;

    auto rasterizer = this->create_Rasterizer();
    auto multisampling = this->create_Multisampling();
    auto depthStencil = this->create_DepthStencil();
    
    
    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT |
                                        VK_COLOR_COMPONENT_G_BIT |
                                        VK_COLOR_COMPONENT_B_BIT |
                                        VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_TRUE;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorBlendAttachment.colorBlendOp        = VK_BLEND_OP_ADD;
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorBlendAttachment.alphaBlendOp        = VK_BLEND_OP_ADD;
    
    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    auto pipeline_layout_info = this->create_PipelineLayout();
    check(
        vkCreatePipelineLayout(this->virtual_device, &pipeline_layout_info, nullptr, &this->pipeline_layout),
        "Failed to create pipeline layout"
    );
    VkGraphicsPipelineCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    create_info.stageCount = 2;
    create_info.pStages = shaderStages;
    create_info.pVertexInputState = &vertexInput;
    create_info.pInputAssemblyState = &inputAssembly;
    create_info.pViewportState = &viewportState;
    create_info.pRasterizationState = &rasterizer;
    create_info.pMultisampleState = &multisampling;
    create_info.pDepthStencilState = &depthStencil;
    create_info.pColorBlendState = &colorBlending;
    create_info.layout = this->pipeline_layout;
    create_info.renderPass = this->render_pass;
    create_info.subpass = 0;
    check(
        vkCreateGraphicsPipelines(this->virtual_device,VK_NULL_HANDLE, 1,&create_info, nullptr, &this->graphic_conv),
        "Failed to create grpahic pipeline"
    );
    
    
    vkDestroyShaderModule(this->virtual_device, this->vert_shader, nullptr);
    vkDestroyShaderModule(this->virtual_device, this->frag_shader, nullptr);
    
}
vector<char> Artifex::read_shader(string path){
    ifstream file(path,ios::ate | ios::binary);
    
    if(!file.is_open()){
        ErrorNotiffication( "Failed to open shader: " + path ,"abyss/src/init_gpu/createGraphicPipeline.cpp");
    }
    size_t fileSize = static_cast<size_t>(file.tellg());
    vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();
    return buffer;
}
VkShaderModule Artifex::create_ShaderModule(const vector<char>& code){
    VkShaderModuleCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    create_info.codeSize = code.size();
    create_info.pCode = reinterpret_cast<const uint32_t*>(code.data());
    VkShaderModule shaderModule;
    if(vkCreateShaderModule(this->virtual_device, &create_info, nullptr, &shaderModule) != VK_SUCCESS){
        ErrorNotiffication( "Failed to create shader module: " ,"abyss/src/init_gpu/createGraphicPipeline.cpp");
        exit(EXIT_FAILURE);
    }
    return shaderModule;
}
VkPipelineShaderStageCreateInfo Artifex::create_FragShaderStage(){
    this->frag_shader = this->create_ShaderModule(
        this->read_shader(Resources::path_system_shaders + "/fragment.spv")
    );

    VkPipelineShaderStageCreateInfo r{};
    r.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    r.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    r.module = this->frag_shader;
    r.pName = "main";
    return r;
}

VkPipelineShaderStageCreateInfo Artifex::create_VertShaderStage(){
    this->vert_shader = this->create_ShaderModule(
        this->read_shader(Resources::path_system_shaders + "/vertex.spv")
    );
    
    VkPipelineShaderStageCreateInfo r{};
    r.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    r.stage =  VK_SHADER_STAGE_VERTEX_BIT;
    r.module = this->vert_shader;
    r.pName = "main";
    return r;
}

VkPipelineVertexInputStateCreateInfo Artifex::create_VertexInput(){
    static auto bindingDescription = Artifex::Vertex::getBindDesc();

    static auto attributeDescriptions = Artifex::Vertex::getAttrDesc();

    VkPipelineVertexInputStateCreateInfo r{};
    r.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    r.vertexBindingDescriptionCount = 1;
    r.pVertexBindingDescriptions = &bindingDescription;

    r.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
    r.pVertexAttributeDescriptions = attributeDescriptions.data();
    return r;

}

VkPipelineInputAssemblyStateCreateInfo Artifex::create_InputAssembly(){
    VkPipelineInputAssemblyStateCreateInfo r{};
    r.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    r.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    r.primitiveRestartEnable = VK_FALSE;
    return r;
}


VkPipelineRasterizationStateCreateInfo Artifex::create_Rasterizer(){
    VkPipelineRasterizationStateCreateInfo r{};
    r.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    r.depthClampEnable = VK_FALSE;
    r.rasterizerDiscardEnable = VK_FALSE;
    r.polygonMode = VK_POLYGON_MODE_FILL;
    r.lineWidth = 1.0f;
    r.cullMode = VK_CULL_MODE_BACK_BIT;
    r.frontFace = VK_FRONT_FACE_CLOCKWISE;
    r.depthBiasEnable = VK_FALSE;
    return r;
} 
VkPipelineMultisampleStateCreateInfo Artifex::create_Multisampling(){
    VkPipelineMultisampleStateCreateInfo r{};
    r.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    r.sampleShadingEnable = VK_FALSE;
    r.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    return r;
}
VkPipelineDepthStencilStateCreateInfo Artifex::create_DepthStencil(){
    VkPipelineDepthStencilStateCreateInfo r{};
    r.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    r.depthTestEnable = VK_TRUE;
    r.depthWriteEnable = VK_TRUE;
    r.depthCompareOp = VK_COMPARE_OP_LESS;
    r.depthBoundsTestEnable = VK_FALSE;
    r.stencilTestEnable = VK_FALSE;
    
    return r;
}   




VkPipelineLayoutCreateInfo  Artifex::create_PipelineLayout(){
    VkPipelineLayoutCreateInfo r{};
    r.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    r.setLayoutCount = 1;     
    r.pSetLayouts = &this->descriptor_set_layout;
    r.pushConstantRangeCount = 0;
    r.pPushConstantRanges = nullptr;
    r.flags = 0;         

    return r;
}




void Artifex::destroyGraphicPipeline(){
    if (graphic_conv) vkDestroyPipeline(virtual_device, graphic_conv, nullptr);
}


void Artifex::destroyPipelineLayout(){
    if (pipeline_layout) vkDestroyPipelineLayout(virtual_device, pipeline_layout, nullptr);
}


void Artifex::destroyShaders(){
    if (vert_shader) vkDestroyShaderModule(virtual_device, vert_shader, nullptr);
    if (frag_shader) vkDestroyShaderModule(virtual_device, frag_shader, nullptr);
}