#include <iostream>
#include "Application.hpp"
#include "ArgParser.hpp"

int main(int argc, char* argv[])
{
    ArgParser args(argc, argv);
    Application::Init();
    Application a = Application(args);
    a.MainLoop();


}