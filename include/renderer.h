#pragma once
#include "RHIDevice.h"
#include "RHICommandBuffer.h"
#include "RHIRenderTarget.h"
#include "RenderGraph.h"
#include "RenderPass.h"

class Renderer 
{
    private:
        RHIDevice* device;
        RHICommandBuffer* commandBuffer;
        RenderGraph renderGraph;
        RHIRenderTarget* mainRenderTarget;
        //TODO - IMPLEMENT THESE
        // ShaderLibrary shaderLibrary;
    public:
        void init(RHIDevice* ConcreteDevice,RHIRenderTarget* mainRT);
        void beginFrame();
        //void submitMesh(/*Mesh*/);
        //void submitLight(/*Light*/);
        //void setCamera(/*Camera*/);
        void endFrame();
        RHIDevice* getDevice();
        RHIRenderTarget* getMainRenderTarget();
};