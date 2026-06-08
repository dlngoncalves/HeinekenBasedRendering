#include "window.h"
#include <iostream>
#include <glm/glm.hpp>

void Window::init(WindowConfig config) 
{
    glfwSetErrorCallback(Window::errorCallback);

    if(!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef ENGINE_PLATFORM_MAC
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required for macOS execution
#endif

    handle = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, nullptr);
    if (!handle) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwWindowHint (GLFW_SAMPLES, 0);
}

void Window::pollEvents() 
{
    glfwPollEvents();
}

void Window::swapBuffers() 
{
    glfwSwapBuffers(handle);
}

bool Window::shouldClose() const 
{
    return glfwWindowShouldClose(handle);
}

void* Window::getNativeHandle() 
{
    return static_cast<void*>(handle);
}

void Window::shutdown() 
{
    glfwDestroyWindow(handle);
    glfwTerminate();
}

Window::~Window()
{
    shutdown();
}

void Window::errorCallback(int error, const char* description) 
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

glm::ivec2 Window::getSize() const 
{
    int width, height;
    glfwGetWindowSize(handle, &width, &height);
    return glm::ivec2(width, height);
}

glm::vec2 Window::getframebufferSize() const 
{
    int width, height;
    glfwGetFramebufferSize(handle, &width, &height);
    return glm::vec2(width, height);
}