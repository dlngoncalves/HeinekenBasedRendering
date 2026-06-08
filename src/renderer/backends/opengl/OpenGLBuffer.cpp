#include "OpenGLBuffer.h"


//I don't know if creating this function JUST to use the initializer list is better than doing the switch inside the constructor body.
namespace {
    GLenum toGLTarget(BufferUsage usage) {
        switch(usage) {
            case BufferUsage::VERTEX:  return GL_ARRAY_BUFFER;
            case BufferUsage::INDEX:   return GL_ELEMENT_ARRAY_BUFFER;
            case BufferUsage::UNIFORM: return GL_UNIFORM_BUFFER;
        }
    }
}

OpenGLBuffer::OpenGLBuffer(const BufferDesc& desc)
    : bufferID(0)
    ,glTarget(toGLTarget(desc.usage))
    ,usage(desc.usage)
{
    glGenBuffers(1, &bufferID);
};

void OpenGLBuffer::upload(const void* data, size_t size) 
{
    glBindBuffer(glTarget, bufferID);
    glBufferData(glTarget, size, data, GL_STATIC_DRAW); // Usage can be parameterized
};

void OpenGLBuffer::bind() 
{
    glBindBuffer(glTarget, bufferID);
};

OpenGLBuffer::~OpenGLBuffer()
{
    Release();
}

void OpenGLBuffer::Release()  
{
    if (bufferID != 0) {
        glDeleteBuffers(1, &bufferID);
    }
}