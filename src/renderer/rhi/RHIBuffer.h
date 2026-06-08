#pragma once
#include <cstddef>

class RHIBuffer
{
    public:
        RHIBuffer() = default;
        //No copy semantics to avoid ownership issues
        RHIBuffer(const RHIBuffer&) = delete;
        RHIBuffer& operator=(const RHIBuffer&) = delete;

        virtual ~RHIBuffer() = default;
        virtual void Release() = 0;
        virtual void upload(const void* data, size_t size) = 0;
        virtual void bind() = 0;
};