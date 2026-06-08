#include "OpenGLCommandBuffer.h"
#include "OpenGLRenderTarget.h"
#include "gl_api.h"

void OpenGLCommandBuffer::beginRenderPass(RHIRenderTarget* renderTarget) 
{
    // Bind the framebuffer associated with the render target
    //auto* glRenderTarget = dynamic_cast<OpenGLRenderTarget*>(renderTarget);
    if (auto* glRenderTarget = dynamic_cast<OpenGLRenderTarget*>(renderTarget)) 
    {
        glRenderTarget->bind();
        glRenderTarget->clear(0.1f, 0.1f, 0.1f, 1.0f); // Clear with a dark gray color
    }
    else
    {
        // If the render target is not an OpenGLRenderTarget, we might want to handle this case (e.g., throw an error)
        throw std::runtime_error("Invalid render target type for OpenGLCommandBuffer");
    }
}

void OpenGLCommandBuffer::endRenderPass(RHIRenderTarget* renderTarget) 
{
    if (auto* glRenderTarget = dynamic_cast<OpenGLRenderTarget*>(renderTarget)) 
    {
        glRenderTarget->unbind();
    }
    else
    {
        throw std::runtime_error("Invalid render target type for OpenGLCommandBuffer");
    }
}

void OpenGLCommandBuffer::bindPipeline(RHIPipeline* pipeline) 
{
    // Cast to OpenGLPipeline and bind the shader program
    //auto* glPipeline = dynamic_cast<OpenGLPipeline*>(pipeline);
    //if (glPipeline) {
    //    glUseProgram(glPipeline->getProgramId());
    //}
}

void OpenGLCommandBuffer::bindVertexBuffer(RHIBuffer* buf) 
{
    // Cast to OpenGLBuffer and bind the vertex buffer
    //auto* glBuffer = dynamic_cast<OpenGLBuffer*>(buf);
    //if (glBuffer) {
    //    glBindBuffer(GL_ARRAY_BUFFER, glBuffer->getBufferId());
    //}
}

void OpenGLCommandBuffer::bindIndexBuffer(RHIBuffer* buf) 
{
    // Cast to OpenGLBuffer and bind the index buffer
    //auto* glBuffer = dynamic_cast<OpenGLBuffer*>(buf);
    //if (glBuffer) {
    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glBuffer->getBufferId());
    //}
}

void OpenGLCommandBuffer::bindUniformBuffer(RHIBuffer* buf, int slot) 
{
    // Cast to OpenGLBuffer and bind the uniform buffer to the specified slot
    //auto* glBuffer = dynamic_cast<OpenGLBuffer*>(buf);
    //if (glBuffer) {
    //    glBindBufferBase(GL_UNIFORM_BUFFER, slot, glBuffer->getBufferId());
    //}
}

void OpenGLCommandBuffer::bindTexture(RHITexture* tex, int slot) 
{
    // Cast to OpenGLTexture and bind the texture to the specified slot
    if (auto* glTexture = dynamic_cast<OpenGLTexture*>(tex)) 
    {
        glTexture->bind(slot);
    }
    else
    {
        throw std::runtime_error("Invalid texture type for OpenGLCommandBuffer");
    }
}