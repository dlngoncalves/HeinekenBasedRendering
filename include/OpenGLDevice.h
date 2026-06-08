#pragma once
#include "gl_api.h"
#include "RHIDevice.h"
#include "RHIBuffer.h"
#include "RHITexture.h"
#include "RHIPipeline.h"
#include "RHIRenderTarget.h"
#include "RHICommandBuffer.h"
#include "window.h"
#include "RHITypes.h"
#include "imgui.h"

class OpenGLDevice : public RHIDevice
{
    private:
         GLFWwindow* glfwHandle;  // OpenGL backend needs direct access to the window for context management
    public:
        ~OpenGLDevice() override;
        void init(void* nativeHandle) override;
        std::unique_ptr<RHIBuffer> createBuffer(const BufferDesc& desc) override;
        std::unique_ptr<RHITexture> createTexture(const TextureDesc& desc) override;
        std::unique_ptr<RHIPipeline> createPipeline(const PipelineDesc& desc) override;
        std::unique_ptr<RHIRenderTarget> createRenderTarget(const RenderTargetDesc& desc) override;
        std::unique_ptr<RHICommandBuffer> createCommandBuffer() override;
        void renderImGuiDrawData(ImDrawData* drawData) override;
        glm::ivec2 getFramebufferSize() override;
        void beginFrame() override;
        void endFrame() override;
        void shutdown() override;
};
