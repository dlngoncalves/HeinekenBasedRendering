#pragma once
#include "RHIRenderTarget.h"
#include "RHIPipeline.h"
#include "RHIBuffer.h"
#include "RHITexture.h"

class RHICommandBuffer 
{
    public:
        virtual ~RHICommandBuffer() = default; 
        virtual void beginRenderPass(RHIRenderTarget* renderTarget) = 0;
        virtual void endRenderPass(RHIRenderTarget* renderTarget) = 0;
        virtual void bindPipeline(RHIPipeline* pipeline) = 0;
        virtual void bindVertexBuffer(RHIBuffer* buf) = 0;
        virtual void bindIndexBuffer(RHIBuffer* buf) = 0;
        virtual void bindUniformBuffer(RHIBuffer* buf, int slot) = 0;
        virtual void bindTexture(RHITexture* tex, int slot) = 0;
        virtual void setViewport(int x, int y, int width, int height) = 0;
        virtual void drawIndexed(int count, int offset) = 0;
        virtual void submit() = 0;
};