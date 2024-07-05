#include "WindowEventHandler.hpp"
#include "Window.hpp"
#include "Application.hpp"

WindowEventHandler* WindowEventHandler::s_Instance;
bool WindowEventHandler::s_Initialized;
GLFWwindow* WindowEventHandler::s_Window;


void WindowEventHandler::Init(GLFWwindow* window)
{
    glfwSetWindowPosCallback(window, WindowEventHandler::WindowPosCallback);
    glfwSetWindowSizeCallback(window, WindowEventHandler::WindowSizeCallback);
    glfwSetWindowCloseCallback(window, WindowEventHandler::WindowCloseCallback);
    glfwSetWindowRefreshCallback(window, WindowEventHandler::WindowRefreshCallback);
    glfwSetWindowFocusCallback(window, WindowEventHandler::WindowFocusCallback);
    glfwSetWindowIconifyCallback(window, WindowEventHandler::WindowIconifyCallback);
    glfwSetWindowMaximizeCallback(window, WindowEventHandler::WindowMaximizeCallback);
    glfwSetFramebufferSizeCallback(window, WindowEventHandler::FramebufferSizeCallback);
    glfwSetWindowContentScaleCallback(window, WindowEventHandler::ContentScaleCallback);

    s_Initialized = true;
    s_Window = window;
}


WindowEventHandler *WindowEventHandler::GetInstance()
{
    if (s_Initialized)
        return s_Instance;
    else
        return NULL;
}

void WindowEventHandler::WindowPosCallback(GLFWwindow *window, int xpos, int ypos)
{
    Application* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
    app->OnMove(xpos, ypos);
}

void WindowEventHandler::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    Application* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
    app->OnResize(width, height);
}

void WindowEventHandler::WindowCloseCallback(GLFWwindow* window)
{
    Application* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
    app->OnClose();
}

void WindowEventHandler::WindowRefreshCallback(GLFWwindow* window)
{
    Application* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
    app->OnRefresh();
}

void WindowEventHandler::WindowFocusCallback(GLFWwindow* window, int focused)
{
    Application* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
    app->OnFocus(focused);
}

void WindowEventHandler::WindowIconifyCallback(GLFWwindow* window, int iconified)
{
    Application* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
    app->OnIconify(iconified);
}

void WindowEventHandler::WindowMaximizeCallback(GLFWwindow* window, int maximized)
{
    Application* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
    app->OnMaximize(maximized);
}

void WindowEventHandler::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    Application* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
    app->OnFramebufferResize(width, height);
}

void WindowEventHandler::ContentScaleCallback(GLFWwindow* window, float width, float height)
{
    Application* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
    app->OnContentScale(width, height);
}

void WindowEventHandler::GLFWErrorCallback(int error_code, const char* description)
{
    Application* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(s_Window));
    app->OnWindowError(error_code, description);
}

void WindowEventHandler::KeyCallback(GLFWwindow* window, int key, int action, int mods)
{
    Application* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(s_Window));
    app->OnKey(key, action);
}

void WindowEventHandler::MouseKeyCallback(GLFWwindow* window, int button, int action, int mods)
{
    Application* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(s_Window));
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    app->OnClick(x, y, button, action);
}