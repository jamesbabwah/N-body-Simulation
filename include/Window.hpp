#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "WindowEventHandler.hpp"

// Simple wrapper for GLFWWindow
class Window
{
public:
    Window(int height, int width, const char* title, int xpos, int ypos);
    ~Window();


private:
    WindowEventHandler m_EventHandler;
    GLFWwindow* m_Window; // Pointer for underlying window
    int m_Height, m_Width;
    int m_x, m_y; // Window coordinates
    bool m_Focused, m_Iconified, m_Maximized;

    //Window Events
    void OnMove(int xpos, int ypos);
    void OnResize(int width, int height);
    void OnClose();
    void OnRefresh();
    void OnFocus(int focused);
    void OnIconify(int iconified);
    void OnMaximize(int maximized);
    void OnFramebufferResize(int width, int height);
    void OnContentScale(float xscale, float yscale);

    friend WindowEventHandler;
};

#endif //WINDOW_HPP