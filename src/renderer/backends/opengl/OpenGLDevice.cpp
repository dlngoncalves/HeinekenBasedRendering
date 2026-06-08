#include "OpenGLDevice.h"
#include "OpenGLBuffer.h"
#include "OpenGLRenderTarget.h"
#include "OpenGLTexture.h"
#include "OpenGLPipeline.h"
#include "OpenGLCommandBuffer.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "gl_api.h"
#include <glm/glm.hpp>
#ifndef ENGINE_PLATFORM_MAC
    #include <GL/glew.h>
#endif

void OpenGLDevice::init(void* nativeHandle) 
{
    // Store the GLFW window handle for context management
    glfwHandle = static_cast<GLFWwindow*>(nativeHandle);

    // Make the OpenGL context current
    glfwMakeContextCurrent(glfwHandle);

#ifndef ENGINE_PLATFORM_MAC
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }
#endif

    // Initialize ImGui for OpenGL
    ImGui_ImplGlfw_InitForOpenGL(glfwHandle, true);
    ImGui_ImplOpenGL3_Init("#version 410");
};

glm::ivec2 OpenGLDevice::getFramebufferSize() 
{
    int width, height;
    glfwGetFramebufferSize(glfwHandle, &width, &height);
    return glm::ivec2(width, height);
}

void OpenGLDevice::beginFrame() 
{
    //auto framebufferSize = getFramebufferSize(glfwHandle);
    glm::ivec2 framebufferSize = getFramebufferSize();
    glViewport(0, 0, framebufferSize.x, framebufferSize.y);
    // Clear the screen at the start of each frame
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLDevice::endFrame() 
{
   
}

OpenGLDevice::~OpenGLDevice() 
{
    shutdown();
}

void OpenGLDevice::shutdown() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwMakeContextCurrent(nullptr);
}

std::unique_ptr<RHIBuffer> OpenGLDevice::createBuffer(const BufferDesc& desc) 
{
    return std::make_unique<OpenGLBuffer>(desc);
};

std::unique_ptr<RHITexture> OpenGLDevice::createTexture(const TextureDesc& desc)
{
    return std::make_unique<OpenGLTexture>(desc);
};

std::unique_ptr<RHIPipeline> OpenGLDevice::createPipeline(const PipelineDesc& desc) 
{
    return std::make_unique<OpenGLPipeline>(desc);
};

std::unique_ptr<RHIRenderTarget> OpenGLDevice::createRenderTarget(const RenderTargetDesc& desc) 
{
    return std::make_unique<OpenGLRenderTarget>(desc);
};

std::unique_ptr<RHICommandBuffer> OpenGLDevice::createCommandBuffer()
{
    // return std::make_unique<OpenGLCommandBuffer>();
    return nullptr; // Placeholder until OpenGLCommandBuffer is implemented
}

void OpenGLDevice::renderImGuiDrawData(ImDrawData* drawData) 
{
    ImGui_ImplOpenGL3_RenderDrawData(drawData);
}

        // void init(void* nativeHandle);
        // std::unique_ptr<RHIBuffer> createBuffer(BufferDesc desc);
        // std::unique_ptr<RHITexture> createTexture(TextureDesc desc);
        // std::unique_ptr<RHIPipeline> createPipeline(PipelineDesc desc);
        // std::unique_ptr<RHIRenderTarget> createRenderTarget(RTDesc desc);
        // std::unique_ptr<RHICommandBuffer> createCommandBuffer();
        // void renderImGuiDrawData(ImDrawData* drawData);
        // void beginFrame();
        // void endFrame();
        // void shutdown();

// class OpenGLDevice {
//         -GLFWwindow* glfwHandle
//         +init(window Window) void
//         +createBuffer(desc) RHIBuffer*
//         +createTexture(desc) RHITexture*
//         +createPipeline(desc) RHIPipeline*
//         +createRenderTarget(desc) RHIRenderTarget*
//         +createCommandBuffer() RHICommandBuffer*
//         +beginFrame() void
//         +endFrame() void
//         +shutdown() void
//     }
//     note for OpenGLDevice "init() calls:\n  glfwMakeContextCurrent()\n  gladLoadGL()\n  ImGui_ImplGlfw_InitForOpenGL()\n  ImGui_ImplOpenGL3_Init()\nshutdown() cleans up ImGui + context"
//note for OpenGLDevice :
//"init() calls:
//glfwMakeContextCurrent()
//gladLoadGL()
//ImGui_ImplGlfw_InitForOpenGL()
//ImGui_ImplOpenGL3_Init()
//shutdown() cleans up ImGui + context"