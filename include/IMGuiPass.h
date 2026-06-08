#pragma once
#include "RenderPass.h"
#include "RHIDevice.h"

class IMGuiPass : public RenderPass
{
    private:
        RHIDevice* device;
    public:
        IMGuiPass(RHIDevice* concreteDevice);
        void execute(const RHICommandBuffer& cmd) override;
        std::string getName() override;
};