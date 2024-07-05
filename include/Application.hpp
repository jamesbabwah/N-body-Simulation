#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>
#include <unordered_map>

#include "Window.hpp"
#include "ArgParser.hpp"
#include "Timer.hpp"
#include "WindowEventHandler.hpp"



class Application
{
public:
    Application(ArgParser args);

    // Initalizes GLFW
    // Must be called before constructing Application otherwise window will not be created
    static void Init();

    void MainLoop();

    Window* GetWindow();
    bool isRunning();
    bool isPaused();

private:
    Window m_Window;
    Timer m_Timer;

    bool m_Running;
    bool m_Paused;

    //IModel m_SimModel; TBA

    static bool m_Initialized;


    // Input Events
    void OnClick(double x, double y, int button, int action);
    void OnKey(int key, int action);

    // Cache of state of recently updated keys (true for pressed, false for not pressed)
    std::unordered_map<int, bool> m_Keys;
    // Queries state of key
    bool isKeyPressed(int key);

    //Window Events - will forward events to necessary components
    void OnMove(int xpos, int ypos);
    void OnResize(int width, int height);
    void OnClose();
    void OnRefresh();
    void OnFocus(int focused);
    void OnIconify(int iconified);
    void OnMaximize(int maximized);
    void OnFramebufferResize(int width, int height);
    void OnContentScale(float xscale, float yscale);

    // Error Handling
    void OnWindowError(int error_code, std::string description);

    friend WindowEventHandler;
};

#endif //APPLICATION_HPP