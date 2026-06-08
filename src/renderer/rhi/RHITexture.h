#pragma once
#include <cstddef>
#include "RHITypes.h"

class RHITexture 
{
    public:
        RHITexture() = default;
        //No copy semantics to avoid ownership issues
        RHITexture(const RHITexture&) = delete;
        RHITexture& operator=(const RHITexture&) = delete;

        virtual ~RHITexture() = default;
        virtual void Release() = 0;
        virtual void upload(const void* data, const TextureDesc& desc) = 0;
        virtual void setDesc(const TextureDesc& desc) = 0;//might be useful;
        virtual TextureDesc getDesc() const = 0; //if we want to query the texture properties later
        virtual void bind(int slot) = 0;
};