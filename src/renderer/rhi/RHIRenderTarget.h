#pragma once
#include "RHITexture.h"
#include <glm/glm.hpp>

class RHIRenderTarget
{
    public:
        virtual ~RHIRenderTarget() = default;
        virtual void init () = 0; // might need to pass desc here later
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void clear(glm::vec4 color, bool clearDepth = true) = 0;
        virtual void clear(float r, float g, float b, float a, bool clearDepth = true) = 0;
        virtual void resolve() = 0;

        virtual int getWidth() = 0;
        virtual int getHeight() = 0;

        // access attachments for use as input textures in subsequent passes
        // virtual RHITexture* getColorAttachment(int index = 0) = 0;
        // virtual RHITexture* getDepthAttachment() = 0;
};