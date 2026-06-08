#pragma once
#include <string>

class RHIPipeline 
{
    public:
        virtual ~RHIPipeline() = default;
        virtual void bind() = 0;
        virtual void setUniform(const std::string& name, const void* value) = 0;
};