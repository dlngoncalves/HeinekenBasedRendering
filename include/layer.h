#pragma once

class Layer {
public:
    virtual ~Layer() = default;
    virtual void OnImGuiRender() = 0; // Pure virtual function for UI code
};