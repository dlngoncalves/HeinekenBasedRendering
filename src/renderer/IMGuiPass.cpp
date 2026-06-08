#include "RenderPass.h"
#include "RHIDevice.h"
#include "IMGuiPass.h"

IMGuiPass::IMGuiPass(RHIDevice* concreteDevice) 
{
    device = concreteDevice;
}

void IMGuiPass::execute(const RHICommandBuffer& cmd) 
{
    ImGui::Render();
    device->renderImGuiDrawData(ImGui::GetDrawData());
}

std::string IMGuiPass::getName() 
{
    return "IMGuiPass";
}