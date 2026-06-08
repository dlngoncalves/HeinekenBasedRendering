#pragma once
#include <iostream>
#include "RenderGraph.h"
#include "RenderPass.h"

void RenderGraph::addPass(RenderPass* pass) 
{
    passes.push_back(pass);
}

void RenderGraph::execute(const RHICommandBuffer& cmd) 
{
    for (auto pass : passes) {
        pass->execute(cmd);
    }
}

void RenderGraph::compile() 
{
    // Analyze passes, determine dependencies, and optimize execution order
    // For now, we'll just print the pass names in order
    for (auto pass : passes) {
        std::cout << "Compiling pass: " << pass->getName() << std::endl;
    }
}