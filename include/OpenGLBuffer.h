#pragma once
#include <cstddef>
#include <memory>
#include "gl_api.h"
#include "RHIBuffer.h"
#include "RHITypes.h"

class OpenGLBuffer : public RHIBuffer
{
    private:
        GLuint bufferID;
        BufferUsage usage;
        GLenum glTarget;
    public:
        OpenGLBuffer(const BufferDesc& desc);
 
        OpenGLBuffer(OpenGLBuffer&& other) noexcept 
        {
            bufferID = other.bufferID;
            other.bufferID = 0;
        }
        
        OpenGLBuffer& operator=(OpenGLBuffer&& other) noexcept 
        {
            if (this != &other) 
            {
                // Delete our old buffer before taking the new one!
                if (bufferID != 0) 
                {
                    glDeleteBuffers(1, &bufferID);
                }
                bufferID = other.bufferID;
                other.bufferID = 0;
            }
            return *this;
        }

        ~OpenGLBuffer() override ;
        void Release() override;
        void upload(const void* data, size_t size) override;
        void bind() override;
};