#include "renderer.h"
#include "RHIRenderTarget.h"
#include <utility>
#include <memory>
void Renderer::init(RHIDevice* ConcreteDevice, std::unique_ptr<RHIRenderTarget> mainRT) 
{
    device = ConcreteDevice;
    mainRenderTarget->bind();
    //device->createCommandBuffer();
    //commandBuffer = device->createCommandBuffer().get();
    // commandBuffer = device->createCommandBuffer();
    // mainRenderTarget = devicedevice->createRenderTarget({1280, 720});
}

RHIDevice* Renderer::getDevice() 
{
    return device;
}

RHIRenderTarget* Renderer::getMainRenderTarget() 
{
    return mainRenderTarget.get();
}

void Renderer::beginFrame() 
{
    device->beginFrame();
    // commandBuffer->beginRenderPass(*mainRenderTarget);
}

void Renderer::endFrame() 
{
    // commandBuffer->endRenderPass();
    device->endFrame();
}

void Renderer::setRenderTarget(std::unique_ptr<RHIRenderTarget>renderTarget)
{
    mainRenderTarget = std::move(renderTarget);
}