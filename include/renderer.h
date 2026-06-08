#pragma once
#include <memory>
#include "RHIDevice.h"
#include "RHICommandBuffer.h"
#include "RHIRenderTarget.h"
#include "RenderGraph.h"
#include "RenderPass.h"

class Renderer 
{
    private:
        RHIDevice* device = nullptr;
        RHICommandBuffer* commandBuffer = nullptr;
        RenderGraph renderGraph;
        std::unique_ptr<RHIRenderTarget> mainRenderTarget;
    public:
        Renderer() = default;
        ~Renderer() = default;
        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        Renderer(Renderer&&) noexcept = default;
        Renderer& operator=(Renderer&&) noexcept = default;

        void init(RHIDevice* ConcreteDevice, std::unique_ptr<RHIRenderTarget> mainRT);
        void beginFrame();
        //void submitMesh(/*Mesh*/);
        //void submitLight(/*Light*/);
        //void setCamera(/*Camera*/);
        void endFrame();
        RHIDevice* getDevice();
        RHIRenderTarget* getMainRenderTarget();
        void setRenderTarget(std::unique_ptr<RHIRenderTarget> renderTarget);
};
