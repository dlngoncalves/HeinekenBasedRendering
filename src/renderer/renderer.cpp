#include "renderer.h"

void Renderer::init(RHIDevice* ConcreteDevice, RHIRenderTarget* mainRT) 
{
    device = ConcreteDevice;
    mainRenderTarget = mainRT;
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
    return mainRenderTarget;
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
