#ifndef WINDOWEVENTHANDLER_HPP
#define WINDOWEVENTHANDLER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <queue>
#include <tuple>


class WindowEventHandler
{
// no clue how to do this without using a singleton (forgive me)
public:
    static void Init(GLFWwindow* window);
    static WindowEventHandler* GetInstance();

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
    static void GLFWErrorCallback(int error_code, const char* description); // Callback for any glfw errors

    static void KeyCallback(GLFWwindow* window, int key, int action, int mods);
    static void MouseKeyCallback(GLFWwindow* window, int button, int action, int mods);

    static bool s_Initialized;
    static WindowEventHandler* s_Instance;
    static GLFWwindow* s_Window;
};
#endif //WINDOWEVENTHANDLER_HPP