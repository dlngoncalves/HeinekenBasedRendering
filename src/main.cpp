#include <iostream>

// #define STB_IMAGE_IMPLEMENTATION
// //#include "stb_image.h"

// #define STB_IMAGE_WRITE_IMPLEMENTATION
// //#include "stb_image_write.h"

// #define TINYGLTF_IMPLEMENTATION
// #include "tiny_gltf.h"

// Include your windowing tool
#include <GLFW/glfw3.h>

// Include Dear ImGui backends
#include "imgui.h"
//Not sure we need these here - I think only imgui.h is needed
//when calling UI code, the other two are needed to initialize the backends
// and render the UI, but I don't think we need them in main.cpp. We can always move them later if we need to.
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//Probably should move these to the camera class, and some imput class
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "window.h"
#include "application.h"

WindowConfig config = {
    1280, 720, "HBR Engine Sandbox", true, true
};

int main() {

    // Window window;
    // //Gonna do something ugly here
    // GLFWwindow* glfw_window = nullptr;
    // try
    // {
    //     window.init(config);
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << std::endl;
    //     // window.shutdown(); Dont think we need to shutdown if init OR window creation failed.
    //     return -1;
    // }
  
    //glfw_window = static_cast<GLFWwindow*>(window.getNativeHandle());

    Application* app = new Application();
    app->init(config);

    app->run();

    delete app;
    
    // 3. Initialize Dear ImGui
    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    // // Set a clean, modern dark visual style
    // ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    //ImGui_ImplGlfw_InitForOpenGL(glfw_window, true);
    //ImGui_ImplOpenGL3_Init("#version 410 core"); // Matches Mac target limits

    // 4. Main Core Execution Loop
    // while(!window.shouldClose())
    // {
    //     window.pollEvents();
    // };

    // while (!glfwWindowShouldClose(glfw_window)) {
    //     glfwPollEvents();

    //     // Start the Dear ImGui frame
    //     ImGui_ImplOpenGL3_NewFrame();
    //     ImGui_ImplGlfw_NewFrame();
    //     ImGui::NewFrame();

    //     // --- RENDER IMGUI INTERFACE ---
    //     ImGui::Begin("Engine Diagnostics");
    //     ImGui::Text("Application Performance: %.3f ms/frame (%.1f FPS)",
    //                 1000.0f / io.Framerate, io.Framerate);
    //     ImGui::End();

    //     // --- RENDER OPENGL GRAPHICS ---
    //     int display_w, display_h;
    //     glfwGetFramebufferSize(glfw_window, &display_w, &display_h); // Handles Retina Screen Scaling
    //     glViewport(0, 0, display_w, display_h);
        
    //     // Clean the screen buffer with a dark grey backdrop
    //     glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    //     glClear(GL_COLOR_BUFFER_BIT);

    //     // Finalize ImGui and swap buffers
    //     ImGui::Render();
    //     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
    //     glfwSwapBuffers(glfw_window);
    // }

    // 5. Explicit Cleanup
    // ImGui_ImplOpenGL3_Shutdown();
    // ImGui_ImplGlfw_Shutdown();
    // ImGui::DestroyContext();

    // glfwDestroyWindow(glfw_window);
    // glfwTerminate();
    return 0;
}
