#include "OpenGLTexture.h"
#include "RHITypes.h"
#include "gl_api.h"

namespace {
    GLenum toGLWrap(TextureWrap wrap) {
        switch(wrap) {
            case TextureWrap::Repeat:         return GL_REPEAT;
            case TextureWrap::ClampToEdge:    return GL_CLAMP_TO_EDGE;
            case TextureWrap::MirroredRepeat: return GL_MIRRORED_REPEAT;
        }
    }

    GLenum toGLFilter(TextureFilter filter) {
        switch(filter) {
            case TextureFilter::Nearest:     return GL_NEAREST;
            case TextureFilter::Linear:      return GL_LINEAR;
            case TextureFilter::LinearMipmap: return GL_LINEAR_MIPMAP_LINEAR;
        }
    }

    GLenum toGLFormat(TextureFormat format) {
        switch(format) {
            case TextureFormat::RGBA8: return GL_RGBA;
            case TextureFormat::RGB8:  return GL_RGB;
            case TextureFormat::RG8:   return GL_RG;
            case TextureFormat::DEPTH24_STENCIL8: return GL_DEPTH_STENCIL;
        }
    };

   GLenum toGLInternalFormat(TextureFormat format) {
        switch(format) {
            case TextureFormat::RGBA8:  return GL_RGBA8;
            case TextureFormat::RGB8:   return GL_RGB8;
            case TextureFormat::RGBA16F: return GL_RGBA16F;
            // etc.
        }
    };
}

OpenGLTexture::OpenGLTexture(const TextureDesc& desc)
    : texId(0)
    , texDesc(desc)
{
}

void OpenGLTexture::upload(const void* data, const TextureDesc& desc) 
{
    glGenTextures(1, &texId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexImage2D(GL_TEXTURE_2D, 0, toGLInternalFormat(desc.format), desc.width, desc.height, 0, toGLFormat(desc.format), GL_UNSIGNED_BYTE, data);
    
    if (desc.generateMips) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, toGLWrap(desc.wrapS));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, toGLWrap(desc.wrapT));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toGLFilter(desc.minFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toGLFilter(desc.magFilter));

}

void OpenGLTexture::bind(int slot) 
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texId);
}

OpenGLTexture::~OpenGLTexture() 
{
    Release();
}

void OpenGLTexture::Release() 
{
    if (texId != 0) {
        glDeleteTextures(1, &texId);
        texId = 0;
        texDesc = {};
    }
}

void OpenGLTexture::setDesc(const TextureDesc& desc) 
{
    texDesc = desc;
}

TextureDesc OpenGLTexture::getDesc() const 
{
    return texDesc;
}
