#pragma once
#include "GLFW/glfw3.h"
#include <string>
#include <glm/glm.hpp>

struct WindowConfig
{
    int width;
    int height;
    std::string title;
    bool vsync;
    bool resizable;
};

class Window 
{
    GLFWwindow* handle;  // GLFW is an impl detail, hidden here
public:
    void init(WindowConfig config);
    void pollEvents();
    void swapBuffers();          // only called by OpenGL backend
    bool shouldClose() const;
    glm::ivec2 getSize() const;
    glm::vec2 getframebufferSize() const;
    void* getNativeHandle();     // escape hatch: returns GLFWwindow* for
                                 // ImGui init, Vulkan surface creation, etc.
    void shutdown();
    static void errorCallback(int error, const char* description);
};