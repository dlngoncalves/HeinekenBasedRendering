#pragma once
#include "RHIPipeline.h"
#include "RHITypes.h"
#include "gl_api.h"
#include <unordered_map>
#include <string>

class OpenGLPipeline : public RHIPipeline 
{
    GLuint programId;
    std::unordered_map<std::string, GLint> uniformCache;
    
    public:
        OpenGLPipeline(const PipelineDesc& desc);
        ~OpenGLPipeline() override;
        void bind() override;
        void setUniform(const std::string& name, const void* value) override;

    private:
        GLuint compileShader(const std::string& source, GLenum type);
        void linkProgram(GLuint vert, GLuint frag);
        bool readFile(const std::string& path, std::string& outContents);
};

