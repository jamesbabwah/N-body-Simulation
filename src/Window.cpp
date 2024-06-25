#include "Window.hpp"
#include <iostream>
#include <cstdlib>

//Assumes GLFW is initialized
Window::Window(int height, int width, const char* title, int xpos, int ypos)
    : m_Window(glfwCreateWindow(width, height, title, NULL, NULL)), m_Height(height), m_Width(width), m_x(xpos), m_y(ypos), m_EventHandler(m_Window)
{
    if(m_Window == NULL)
    {
        std::cout << "Window could not be created" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwSetWindowPos(m_Window, xpos, ypos);

    glfwSetWindowUserPointer(m_Window, reinterpret_cast<void*>(this));
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
}

void Window::OnMove(int xpos, int ypos)
{
    m_x = xpos;
    m_y = ypos;
}

void Window::OnResize(int width, int height)
{
    m_Width = width;
    m_Height = height;
}

void Window::OnClose(){}
void Window::OnRefresh(){}
void Window::OnFocus(int focused)
{
    m_Focused = focused;
}
void Window::OnIconify(int iconified)
{
    m_Iconified = iconified;
}
void Window::OnMaximize(int maximized)
{
    m_Maximized = maximized;
}
void Window::OnFramebufferResize(int width, int height){}
void Window::OnContentScale(float xscale, float yscale){}


