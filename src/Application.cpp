#include "Application.hpp"
#include "WindowEventHandler.hpp"
#include <iostream>

bool Application::m_Initialized;

Application::Application(ArgParser args)
    : m_Window(args.getWindowHeight(), args.getWindowWidth(), "N Body Simulation", 200, 200),
    m_Running(true),
    m_Paused(false)
{
    glfwSetWindowUserPointer(m_Window.GetWindow(), reinterpret_cast<void*>(this));
    WindowEventHandler::Init(m_Window.GetWindow());
}

// Must call before initializing class
void Application::Init()
{
    if(!m_Initialized)
    {    if(!glfwInit())
        {
            std::cout << "Could not initialize GLFW" << std::endl;
            exit(EXIT_FAILURE);
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
}

void Application::MainLoop()
{
    while (isRunning())
    {
        if(!isPaused())
        {
            m_Timer.Tick();
            m_Window.Update();
        }
        glfwPollEvents();
    }
}

Window* Application::GetWindow()
{
    return &m_Window;
}

bool Application::isRunning()
{
    return m_Running;
}

bool Application::isPaused()
{
    return m_Paused;
}

void Application::OnClick(double x, double y, int button, int action)
{
    if(action == GLFW_PRESS)
    {
        m_Keys[button] = true;
    }
    else if(action == GLFW_RELEASE)
    {
        m_Keys[button] = false;
    }
}


// Updates the state of already cached keys only
void Application::OnKey(int key, int action)
{
    if(m_Keys.find(key) != m_Keys.end())
    {
        if (action == GLFW_PRESS)
        {
            m_Keys[key] = true;
        }
        else if(action == GLFW_RELEASE)
        {
            m_Keys[key] = false;
        }
    }
}

// Checks cache to find state of key, else queries the state
bool Application::isKeyPressed(int key)
{
    if(m_Keys.find(key) != m_Keys.end())
    {
        return m_Keys[key];
    }
    else
    {
        int state = glfwGetKey(m_Window.GetWindow(), key);
        if (state == GLFW_PRESS || state == GLFW_REPEAT)
        {
            m_Keys[key] = true;
            return true;
        }
        else
        {
            m_Keys[key] = false;
            return false;
        }


    }
}


void Application::OnMove(int xpos, int ypos)
{
    m_Window.OnMove(xpos, ypos);
    std::cout << "Wdinwo move" << std::endl;
}

void Application::OnResize(int width, int height)
{
    m_Window.OnResize(width, height);
    std::cout << "Window resize" << std::endl;
}

void Application::OnClose()
{
    m_Window.OnClose();
    m_Running = false;
    std::cout << "Close" << std::endl;
}

void Application::OnRefresh()
{
    m_Window.OnRefresh();
    std::cout << "Refresh" << std::endl;
}

void Application::OnFocus(int focused)
{
    m_Window.OnFocus(focused);
    std::cout << "Focus" << std::endl;
}

void Application::OnIconify(int iconified)
{
    m_Window.OnIconify(iconified);
    m_Paused = iconified;
    std::cout << "Iconfiy" << std::endl;
}

void Application::OnMaximize(int maximized)
{
    m_Window.OnMaximize(maximized);
    std::cout << "Maximize" << std::endl;
}

void Application::OnFramebufferResize(int width, int height)
{
    m_Window.OnFramebufferResize(width, height);
    std::cout << "FB resize" << std::endl;
}

void Application::OnContentScale(float xscale, float yscale)
{
    m_Window.OnContentScale(xscale, yscale);
    std::cout << "Content scale" << std::endl;
}

void Application::OnWindowError(int error_code, std::string description)
{
    std::cout << "Error: " << description << std::endl;
}
