#include <iostream>
#include "ArgParser.hpp"
#include "Timer.hpp"

int main(int argc, char* argv[])
{
    Timer t;

    t.Init();
    while (t.GetElaspedTime() < 5)
    {
        t.Tick();
        std::cout << "Time: " << t.GetElaspedTime() << " dt: " << t.GetDeltaTime() << std::endl;

    }


}