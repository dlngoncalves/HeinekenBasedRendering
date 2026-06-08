#include "OpenGLRenderTarget.h"
#include "gl_api.h"


void OpenGLRenderTarget::init() 
{
    glGenFramebuffers(1, &fboId);
    glBindFramebuffer(GL_FRAMEBUFFER, fboId);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("Failed to create framebuffer");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind after setup
}

void OpenGLRenderTarget::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fboId);
}

void OpenGLRenderTarget::clear(glm::vec4 color, bool clearDepth) 
{
    glClearColor(color.r, color.g, color.b, color.a);
    GLbitfield bits = GL_COLOR_BUFFER_BIT;
    if (clearDepth) {
        bits |= GL_DEPTH_BUFFER_BIT;
    }
    glClear(bits);
}

void OpenGLRenderTarget::clear(float r, float g, float b, float a, bool clearDepth) 
{
    glClearColor(r, g, b, a);
    GLbitfield bits = GL_COLOR_BUFFER_BIT;
    if (clearDepth) {
        bits |= GL_DEPTH_BUFFER_BIT;
    }
    glClear(bits);
}

void OpenGLRenderTarget::resolve() 
{
    // For a simple implementation, we might not need to do anything here.
    // In a more complex setup with multisampling, this would resolve the multisampled buffer to a texture.
}

void OpenGLRenderTarget::unbind() 
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // Bind the default framebuffer
}

int OpenGLRenderTarget::getWidth()
{
    // Placeholder: return a default width or store it as a member variable
    return 1280; // Example width
}

int OpenGLRenderTarget::getHeight() 
{
    // Placeholder: return a default height or store it as a member variable
    return 720; // Example height
}

// class OpenGLRenderTarget : public RHIRenderTarget {
//     GLuint fboId;
//     std::unique_ptr<OpenGLTexture> colorTexture;
//     std::unique_ptr<OpenGLTexture> depthTexture;
// public:
//     OpenGLRenderTarget(const RenderTargetDesc& desc) {
//         glGenFramebuffers(1, &fboId);
//         glBindFramebuffer(GL_FRAMEBUFFER, fboId);
//         // create and attach color + depth textures
//     }
//     void bind() override {
//         glBindFramebuffer(GL_FRAMEBUFFER, fboId);
//     }
// };