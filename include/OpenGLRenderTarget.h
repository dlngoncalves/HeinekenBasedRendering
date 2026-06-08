#pragma once
#include <memory>
#include "RHIRenderTarget.h"
#include "OpenGLTexture.h"
#include "gl_api.h"

class OpenGLRenderTarget : public RHIRenderTarget
{
    private:
        GLuint fboId;
        RenderTargetDesc desc;
        // With the material class I'm not sure if I need to store these here.
        // std::unique_ptr<OpenGLTexture> colorTexture;
        // std::unique_ptr<OpenGLTexture> depthTexture;
    public:
        OpenGLRenderTarget(const RenderTargetDesc& desc);
        void init() override; // might need to pass desc here later
        void bind() override;
        void unbind() override;
        void clear(glm::vec4 color, bool clearDepth = true) override;
        void clear(float r, float g, float b, float a, bool clearDepth = true) override;
        void resolve() override;

        int getWidth() override;
        int getHeight() override;
};