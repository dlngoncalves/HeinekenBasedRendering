#include <iostream>
#include "application.h"
#include "window.h"
#include "OpenGLDevice.h"
#include "OpenGlRenderTarget.h"
#include "renderer.h"

#ifdef ENGINE_RENDERER_OPENGL
    #include "imgui_impl_opengl3.h"
#endif
#ifdef ENGINE_WINDOWING_GLFW
    #include "imgui_impl_glfw.h"
#endif

// while (!glfwWindowShouldClose(window))
// {
//     // 1. Poll incoming window events (inputs, resizing)
//     glfwPollEvents();

//     // 2. Start the Dear ImGui frame for your backends
//     ImGui_ImplOpenGL3_NewFrame(); // Renderer backend
//     ImGui_ImplGlfw_NewFrame();    // Platform backend (GLFW)
//     ImGui::NewFrame();            // Core Dear ImGui library initialization

//     // 3. Assemble your user interface
//     ImGui::Begin("Hello, world!");
//     ImGui::Text("Your UI goes here.");
//     ImGui::End();

//     // 4. Finalize calculations and render
//     ImGui::Render();
    
//     // Clear screen and draw your frame data
//     glClear(GL_COLOR_BUFFER_BIT);
//     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//     // Swap buffers to display the image
//     glfwSwapBuffers(window);
// }


void Application::init(WindowConfig config) 
{
    try
    {
        window.init(config);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }

    auto glDevice = std::make_unique<OpenGLDevice>();
    
    try
    {
        glDevice->init(window.getNativeHandle());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }

    device = std::move(glDevice);

    auto glRenderTarget = std::make_unique<OpenGLRenderTarget>();
    glRenderTarget->init();

    renderer.init(device.get(), glRenderTarget.get());

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    run();
}

void Application::run() 
{

    // Main application loop
    while (!window.shouldClose()) 
    {
        window.pollEvents();

#ifdef ENGINE_RENDERER_OPENGL
        ImGui_ImplOpenGL3_NewFrame();
#endif
#ifdef ENGINE_WINDOWING_GLFW
        ImGui_ImplGlfw_NewFrame();
#endif

        //ideally we want to avoid calling glfw stuff directly
        double lastFrameTime = glfwGetTime();
        deltaTime = 0.0f;
        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        tick(deltaTime);

        ImGui::NewFrame();

            ImGui::Begin("Engine Diagnostics");
            ImGui::Text("Application Performance: %.3f ms/frame (%.1f FPS)",
                        1000.0f / io.Framerate, io.Framerate);
        
        ImGui::End();

        ImDrawData* drawData = ImGui::GetDrawData();
        renderer.beginFrame();
        renderer.getDevice()->renderImGuiDrawData(drawData);
        renderer.endFrame();
        window.swapBuffers();
    }
};

void Application::tick(double deltaTime) 
{
    renderer.beginFrame();
    renderer.endFrame();
}

Application::~Application() 
{
    shutdown();
}

void Application::shutdown() 
{
    renderer.getDevice()->shutdown();
    window.shutdown();
}