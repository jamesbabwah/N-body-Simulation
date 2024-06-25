#ifndef WINDOWEVENTHANDLER_HPP
#define WINDOWEVENTHANDLER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <queue>
#include <tuple>

enum class WindowEventType
{
    NONE = 0,
    MOVE = 1,
    RESIZE = 2,
    CLOSE = 3,
    REFRESH = 4,
    FOCUS = 5,
    ICONIFY = 6,
    MAXIMIZE = 7,
    FRAMEBUFFERRESIZE = 8,
    CONTENTSCALE = 9,
};

struct WindowEvent
{
    WindowEvent(WindowEventType action); // close/refresh actions
    WindowEvent(WindowEventType action, int param1, int param2); // moving/scaling window/content actions
    WindowEvent(WindowEventType action, float param1, float param2); // scaling content
    WindowEvent(WindowEventType action, bool param1); // maximize/iconify/focus actions
    WindowEventType Action;

    union WindowEventParams
    {
        void* placeholder; // for parameterless events (i.e. close/refresh/none)
        std::tuple<int, int> window_position; //For moving window
        std::tuple<int, int> window_dimensions; // For scaling window
        bool focused; // For shifting focus between windows
        bool iconified; // For minimizing window
        bool maximized; // For maximizing window
        std::tuple<int, int> framebuffer_dimensions; // For scaling framebuffer
        std::tuple<float, float> content_scale; // For scaling content
    } params;
};


class WindowEventHandler
{
// no clue how to do this without using a singleton
public:
    WindowEventHandler(GLFWwindow* window);
    WindowEvent GetEvent();
    bool HasEvents();
private:
    static void WindowPosCallback(GLFWwindow* window, int xpos, int ypos); // Callback for when window is moved
    static void WindowSizeCallback(GLFWwindow* window, int width, int height); // Callback for when window is resized
    static void WindowCloseCallback(GLFWwindow* window); // Callback for when window needs to close
    static void WindowRefreshCallback(GLFWwindow* window);  // Callback for when the window needs to be refreshed (eg if window was covered by another window)
    static void WindowFocusCallback(GLFWwindow* window, int focused);  // Callback for when window loses/gains focus
    static void WindowIconifyCallback(GLFWwindow* window, int iconified); // Callback for when window is iconified or restored
    static void WindowMaximizeCallback(GLFWwindow* window, int maximized); // Callback for when window is maximized or restored
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height); // Callback for when frambuffer is resized
    static void ContentScaleCallback(GLFWwindow* window, float width, float height); // Callback for when window content is scaled

    static std::queue<WindowEvent> s_Events;
};
#endif //WINDOWEVENTHANDLER_HPP