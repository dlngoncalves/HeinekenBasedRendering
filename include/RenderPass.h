#pragma once
#include <string>
#include "RHICommandBuffer.h"
//If needed later, we can add a reference to the device here if we want to allow render passes to create resources on the fly, but for now I want to keep it simple and just pass the command buffer reference.
//If I want to avoid circular dependencies I can forward declare this and include the header in the cpp file.
// Forward declaration to avoid circular dependency
// #include "RHIDevice.h" 

class RenderPass
 {
    public:
        virtual ~RenderPass() = default;
        virtual void execute(const RHICommandBuffer& cmd) = 0;
        virtual std::string getName() = 0;
};