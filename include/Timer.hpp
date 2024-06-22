#ifndef TIMER_HPP
#define TIMER_HPP

#include <ctime>

class Timer
{
public:
    Timer();
    double GetDeltaTime();
    double GetElaspedTime();
    void SetFPS(int fps);
    void Tick();
    void Init();
    // void ShowFPS(Window win); TBI

private:
    double m_DeltaTime = 0;
    double m_LastTime = 0;
    double m_TotalElaspedTime = 0;
    int m_TargetFPS = 0;
    int m_CurrentFPS = 0;
    size_t m_Frames = 0;
    bool m_LimitFPS = false;

    void Sleep(clock_t time);
};

#endif //TIMER_HPP