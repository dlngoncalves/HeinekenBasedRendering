#pragma once
#include "../include/window.h"//probably should organize this better
#include "RHICommandBuffer.h"
#include "RHITexture.h"
#include "RHIPipeline.h"
#include "RHIBuffer.h"
#include "RHITypes.h"
#include "imgui.h"
#include <glm/glm.hpp>

class RHIDevice
{
    public:
        virtual ~RHIDevice() = default;
        virtual void init(void* nativeHandle) = 0;
        virtual std::unique_ptr<RHIBuffer> createBuffer(const BufferDesc& desc) = 0;
        virtual std::unique_ptr<RHITexture> createTexture(const TextureDesc& desc) = 0;
        virtual std::unique_ptr<RHIPipeline> createPipeline(const PipelineDesc& desc) = 0;
        virtual std::unique_ptr<RHIRenderTarget> createRenderTarget(const RenderTargetDesc& desc) = 0;
        virtual std::unique_ptr<RHICommandBuffer> createCommandBuffer() = 0;
        virtual void renderImGuiDrawData(ImDrawData* drawData) = 0;
        virtual glm::ivec2 getFramebufferSize() = 0;
        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;
        virtual void shutdown() = 0;
};