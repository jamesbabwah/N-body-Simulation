#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>


// Simple wrapper for GLFWWindow
class Window
{
public:
    Window(int height, int width, const char* title, int xpos = 0, int ypos = 0);
    Window() = default;
    ~Window();

    GLFWwindow* GetWindow();
    int GetHeight();
    int GetWidth();
    int GetXPos();
    int GetYPos();
    bool IsFocused();
    bool IsIconified();
    bool IsMaximized();
    bool IsOpen();

    void Update();

    //Window Events - Received from Application
    void OnMove(int xpos, int ypos);
    void OnResize(int width, int height);
    void OnClose();
    void OnRefresh();
    void OnFocus(int focused);
    void OnIconify(int iconified);
    void OnMaximize(int maximized);
    void OnFramebufferResize(int width, int height);
    void OnContentScale(float xscale, float yscale);

private:
    GLFWwindow* m_Window; // Pointer for underlying window
    int m_Height, m_Width;
    int m_xPos, m_yPos; // Window coordinates
    bool m_Focused, m_Iconified, m_Maximized;
    bool m_Opened;


};

#endif //WINDOW_HPP