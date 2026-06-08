#pragma once
#include "RenderPass.h"
#include <vector>

class RenderGraph
{
    private:
        std::vector<RenderPass*> passes;
    public:
        void addPass(RenderPass* pass);
        void execute(const RHICommandBuffer& cmd);
        void compile();
};