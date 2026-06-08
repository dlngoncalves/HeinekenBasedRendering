#include "OpenGLPipeline.h"
#include "gl_api.h"
#include <fstream>
#include <sstream>
#include <iostream>

OpenGLPipeline::OpenGLPipeline(const PipelineDesc& desc) 
{

    std::string vertSource, fragSource;
    GLuint vert = 0, frag = 0;

    if (readFile(desc.vertexShaderPath, vertSource)) 
    {
        vert = compileShader(vertSource, GL_VERTEX_SHADER);
    } 
    else 
    {
        std::cerr << "Failed to read vertex shader file: " << desc.vertexShaderPath << std::endl;
    }
    if (readFile(desc.fragmentShaderPath, fragSource)) 
    {
        frag = compileShader(fragSource, GL_FRAGMENT_SHADER);
    } 
    else 
    {
        std::cerr << "Failed to read fragment shader file: " << desc.fragmentShaderPath << std::endl;
    }
    
    if(vert == 0 || frag == 0) 
    {
        std::cerr << "Shader compilation failed. Vertex shader ID: " << vert << ", Fragment shader ID: " << frag << std::endl;
        return;
    }

    linkProgram(vert, frag);
    glDeleteShader(vert);
    glDeleteShader(frag);
}

void OpenGLPipeline::linkProgram(GLuint vert, GLuint frag)
{
    programId = glCreateProgram();

    if (vert != 0) {
        glAttachShader (programId, vert);
    }

    if (frag != 0) {
        glAttachShader (programId, frag);
    }

    //link and check whether the program links fine
    GLint status;
    glLinkProgram (programId);
    glGetProgramiv (programId, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) 
    {
        GLint infoLogLength;
        glGetProgramiv (programId, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog= new GLchar[infoLogLength];
        glGetProgramInfoLog (programId, infoLogLength, NULL, infoLog);
        std::cerr<<"Link log: "<<infoLog<<std::endl;
        delete [] infoLog;
    }
}

OpenGLPipeline::~OpenGLPipeline() 
{
    glDeleteProgram(programId);
}

void OpenGLPipeline::bind() 
{
    glUseProgram(programId);
}

bool OpenGLPipeline::readFile(const std::string& path, std::string& outContents) 
{
    outContents.clear();
    //might need to separate file name from path later
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if(file)
    {
        std::stringstream buffer;
        buffer << file.rdbuf(); 
        outContents = buffer.str();
        return true;
    }
    return false;
}

GLuint compileShader(const std::string& source, GLenum type)
{
    GLuint shader = glCreateShader(type);
    const char* ptmp = source.c_str();
    glShaderSource(shader, 1, &ptmp, NULL);
    glCompileShader(shader); 


    // Check for compilation errors
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) 
    {
        GLint infoLogLength;
        glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog= new GLchar[infoLogLength];
        glGetShaderInfoLog (shader, infoLogLength, NULL, infoLog);
        std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << ((type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT") << "\n" << infoLog << std::endl;
        delete[] infoLog;
        glDeleteShader(shader);
        return 0;//not sure if this is the best way to handle this, but it should be fine for now
    }
    return shader;
}

//hmmm, will need to read my previous implementation of this to remember how I did it, but it should be straightforward to implement. Will need to handle different types of uniforms and cache their locations for performance.
void OpenGLPipeline::setUniform(const std::string& name, const void* value) 
{
    // This is a very basic implementation. In a real engine, you'd want to handle different types and cache uniform locations.
    if (uniformCache.find(name) == uniformCache.end()) {
        uniformCache[name] = glGetUniformLocation(programId, name.c_str());
    }
    GLint location = uniformCache[name];
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader!" << std::endl;
        return;
    }
    // For demonstration, let's assume all uniforms are 4x4 matrices. You would need to expand this to handle different types.
    glUniformMatrix4fv(location, 1, GL_FALSE, static_cast<const GLfloat*>(value));
}