#include "Window.hpp"
#include <iostream>
#include <cstdlib>

//Assumes GLFW is initialized
Window::Window(int height, int width, const char* title, int xpos, int ypos)
    : m_Window(glfwCreateWindow(width, height, title, NULL, NULL)),
    m_Height(height),
    m_Width(width),
    m_xPos(xpos),
    m_yPos(ypos),
    m_Opened(true)
{
    if(m_Window == NULL)
    {
        std::cout << "Window could not be created" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwSetWindowPos(m_Window, xpos, ypos);
    glfwMakeContextCurrent(m_Window);
    gladLoadGL();
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
}

GLFWwindow *Window::GetWindow()
{
    return m_Window;
}

bool Window::IsOpen()
{
    return m_Opened;
}

int Window::GetHeight()
{
    return m_Height;
}

int Window::GetWidth()
{
    return m_Width;
}

int Window::GetXPos()
{
    return m_xPos;
}

int Window::GetYPos()
{
    return m_yPos;
}

bool Window::IsFocused()
{
    return m_Focused;
}

bool Window::IsIconified()
{
    return m_Iconified;
}

bool Window::IsMaximized()
{
    return m_Maximized;
}

/*
Clears color and depth buffers then swaps buffers to render new data
*/
void Window::Update()
{
    int width, height;
    glfwGetFramebufferSize(m_Window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(m_Window);
}

void Window::OnMove(int xpos, int ypos)
{
    m_xPos = xpos;
    m_yPos = ypos;
}

void Window::OnResize(int width, int height)
{
    m_Width = width;
    m_Height = height;
}

void Window::OnClose()
{
    m_Opened = false;
}

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


