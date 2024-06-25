#include "WindowEventHandler.hpp"
#include "Window.hpp"
#include <cassert>

WindowEvent::WindowEvent(WindowEventType action)
    :Action(action), params{nullptr}
{
    if (action != WindowEventType::CLOSE || action != WindowEventType::REFRESH || action != WindowEventType::NONE)
    {
        assert("Initialized WindowEvent with improper parameters");
    }
}

WindowEvent::WindowEvent(WindowEventType action, float param1, float param2)
    :Action(action), params{nullptr}
{
    if(action != WindowEventType::CONTENTSCALE)
    {
        assert("Initialized WindowEvent with improper parameters");
    }
    params.content_scale = {param1, param2};
}

WindowEvent::WindowEvent(WindowEventType action, int param1, int param2)
    :Action(action), params{nullptr}
{
    if (action != WindowEventType::MOVE || action == WindowEventType::RESIZE || action != WindowEventType::FRAMEBUFFERRESIZE)
    {
        assert("Initialized WindowEvent with improper parameters");
    }
    switch (action)
    {
    case WindowEventType::MOVE:
        params.window_position = {param1, param2};
        break;
    case WindowEventType::RESIZE:
        params.window_dimensions = {param1, param2};
        break;
    case WindowEventType::FRAMEBUFFERRESIZE:
        params.framebuffer_dimensions = {param1, param2};
        break;
    default:
        break;
    }
}


WindowEvent::WindowEvent(WindowEventType action, bool param1)
    :Action(action), params{nullptr}
{
    if (action != WindowEventType::FOCUS || action == WindowEventType::ICONIFY || action != WindowEventType::MAXIMIZE)
    {
        assert("Initialized WindowEvent with improper parameters");
    }
    switch (action)
    {
    case WindowEventType::FOCUS:
        params.focused = param1;
        break;
    case WindowEventType::ICONIFY:
        params.iconified = param1;
        break;
    case WindowEventType::MAXIMIZE:
        params.maximized = param1;
        break;
    default:
        break;
    }
}


WindowEventHandler::WindowEventHandler(GLFWwindow* window)
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
}

std::queue<WindowEvent> WindowEventHandler::s_Events;

/*
Returns next event in queue, if there is any
otherwise returns an event of type NONE
Ideally check for events using WindowEventHandler::HasEvents() before getting events
*/
WindowEvent WindowEventHandler::GetEvent()
{
    if(HasEvents())
    {
            WindowEvent new_event = s_Events.front();
        s_Events.pop();

        return new_event;
    }
    else
    {
        return WindowEvent(WindowEventType::NONE);
    }
}

bool WindowEventHandler::HasEvents()
{
    return !s_Events.empty();
}

void WindowEventHandler::WindowPosCallback(GLFWwindow *window, int xpos, int ypos)
{
    WindowEvent new_event = WindowEvent(WindowEventType::MOVE, xpos, ypos);
    s_Events.push(new_event);
    Window* current_window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    current_window->OnMove(xpos, ypos);
}

void WindowEventHandler::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    WindowEvent new_event = WindowEvent(WindowEventType::RESIZE, width, height);
    s_Events.push(new_event);
    Window* current_window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    current_window->OnResize(width, height);
}

void WindowEventHandler::WindowCloseCallback(GLFWwindow* window)
{
    WindowEvent new_event = WindowEvent(WindowEventType::CLOSE);
    s_Events.push(new_event);
    Window* current_window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    current_window->OnClose();
}

void WindowEventHandler::WindowRefreshCallback(GLFWwindow* window)
{
    WindowEvent new_event = WindowEvent(WindowEventType::REFRESH);
    s_Events.push(new_event);
    Window* current_window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    current_window->OnRefresh();
}

void WindowEventHandler::WindowFocusCallback(GLFWwindow* window, int focused)
{
    WindowEvent new_event = WindowEvent(WindowEventType::FOCUS, focused);
    s_Events.push(new_event);
    Window* current_window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    current_window->OnFocus(focused);
}

void WindowEventHandler::WindowIconifyCallback(GLFWwindow* window, int iconified)
{
    WindowEvent new_event = WindowEvent(WindowEventType::ICONIFY, iconified);
    s_Events.push(new_event);
    Window* current_window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    current_window->OnIconify(iconified);
}

void WindowEventHandler::WindowMaximizeCallback(GLFWwindow* window, int maximized)
{
    WindowEvent new_event = WindowEvent(WindowEventType::MAXIMIZE, maximized);
    s_Events.push(new_event);
    Window* current_window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    current_window->OnMaximize(maximized);
}

void WindowEventHandler::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    WindowEvent new_event = WindowEvent(WindowEventType::FRAMEBUFFERRESIZE, width, height);
    s_Events.push(new_event);
    Window* current_window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    current_window->OnFramebufferResize(width, height);
}

void WindowEventHandler::ContentScaleCallback(GLFWwindow* window, float width, float height)
{
    WindowEvent new_event = WindowEvent(WindowEventType::CONTENTSCALE, width, height);
    s_Events.push(new_event);
    Window* current_window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    current_window->OnContentScale(width, height);
}
