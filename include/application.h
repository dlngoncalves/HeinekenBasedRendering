#pragma once
#include "renderer.h"
#include "RHIDevice.h"
#include "window.h"
#include <chrono>

class Application 
{
        // -SceneManager sceneManager
        // -InputSystem input
    private :
        Window window;
        Renderer renderer;
        std::unique_ptr<RHIDevice> device;
        double deltaTime;
        ImGuiIO* io;
        ImGuiContext* UIContext;
        void tick(double deltaTime);
    public:
        Application();
        ~Application();
        void init(WindowConfig config);
        void run(); 
        void shutdown();
};