#include "Timer.hpp"

#include <thread>
#include <chrono>

#include <iostream>


Timer::Timer()
{

}

void Timer::Init()
{
    m_LastTime = (double)(std::clock())/CLOCKS_PER_SEC;
}

double Timer::GetDeltaTime()
{
    return m_DeltaTime;
}

double Timer::GetElaspedTime()
{
    return m_TotalElaspedTime;
}

void Timer::SetFPS(int fps)
{
    m_TargetFPS = fps;
}

void Timer::Tick()
{
    double newTime = (double)(std::clock())/CLOCKS_PER_SEC;
    m_DeltaTime = newTime - m_LastTime;
    if (m_DeltaTime < m_TargetFPS && m_LimitFPS)
    {
        clock_t sleepTime = 1.0/m_TargetFPS - m_DeltaTime;
        Sleep(sleepTime);
        m_TotalElaspedTime += sleepTime;
    }
    m_LastTime = newTime;
    m_TotalElaspedTime += m_DeltaTime;
    m_Frames++;
}

void Timer::Sleep(clock_t time)
{
    std::this_thread::sleep_for(std::chrono::seconds(time/CLOCKS_PER_SEC));
}

