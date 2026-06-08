#pragma once
#include "RHICommandBuffer.h"
#include "RHIRenderTarget.h"
#include "RHIPipeline.h"
#include "RHIBuffer.h"
#include "RHITexture.h"
// #include "OpenGLRenderTarget.h"

class OpenGLCommandBuffer : public RHICommandBuffer 
{
    private:
        //  std::unique_ptr<OpenGLRenderTarget> glRenderTarget;
    public:
        void beginRenderPass(RHIRenderTarget* renderTarget) override;
        void endRenderPass(RHIRenderTarget* renderTarget) override;
        void bindPipeline(RHIPipeline* pipeline) override;
        void bindVertexBuffer(RHIBuffer* buf) override;
        void bindIndexBuffer(RHIBuffer* buf) override;
        void bindUniformBuffer(RHIBuffer* buf, int slot) override;
        void bindTexture(RHITexture* tex, int slot) override;
        void setViewport(int x, int y, int width, int height) override;
        void drawIndexed(int count, int offset) override;
        void submit() override;
};