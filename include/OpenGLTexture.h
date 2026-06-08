#pragma once
#include "RHITexture.h"
#include "RHITypes.h"
#include <cstddef>
#include "gl_api.h"

class OpenGLTexture : public RHITexture 
{
    private:
        GLuint texId;
        TextureDesc texDesc;
    public:
        OpenGLTexture(const TextureDesc& desc);

        OpenGLTexture(OpenGLTexture&& other) noexcept 
        {
            texId = other.texId;
            texDesc = other.texDesc;
            other.texId = 0;
            other.texDesc = {};
        }

        OpenGLTexture& operator=(OpenGLTexture&& other) noexcept 
        {
            if (this != &other) 
            {
                // Delete our old texture before taking the new one!
                if (texId != 0) 
                {
                    glDeleteTextures(1, &texId);
                }
                texId = other.texId;
                texDesc = other.texDesc;
                other.texId = 0;
                other.texDesc = {};
            }
            return *this;
        }
        
        ~OpenGLTexture() override;
        void Release() override;
        void upload(const void* data, const TextureDesc& desc) override;
        void bind(int slot) override;
        void setDesc(const TextureDesc& desc) override;
        TextureDesc getDesc() const override;
};