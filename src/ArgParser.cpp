#include "ArgParser.hpp"
#include <iostream>
#include <string>

ArgParser::ArgParser(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Please specify number of particles (-n) and file containing particle data (-i)" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string arg = argv[1];

    // Display help info
    if (arg == "help")
    {
        // help info (I'll add later)
    }

    for (size_t i = 1; i < argc; i++) // Get number of particles
    {
        arg = argv[i];
        if(arg == "-n")
        {
            if((i + 1) < argc)
            {
                m_NumParticles = std::stoi(argv[i + 1]);
                i++;
            }
            else
            {
                std::cout << "Please specify the number of particles after using the -n flag" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if(arg == "-g") // Get gravitational field strength (optional since there's a default value)
        {
            if((i + 1) < argc)
            {
                m_GravitationalStrength = std::stod(argv[i + 1]);
                i++;
            }
            else
            {
                std::cout << "Please specify the gravitational field strength after using the -g flag" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if(arg == "-t") // Get timestep (optional since there's a default value)
        {
            if((i + 1) < argc)
            {
                m_Timestep = std::stod(argv[i + 1]);
                i++;
            }
            else
            {
                std::cout << "Please specify the timestep after using the -t flag" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if(arg == "-i") // Get file for inital data on particles
        {
            if((i + 1) < argc)
            {
                std::string filepath = argv[i + 1];
                m_ParticleFile = std::ifstream(filepath);
                i++;
            }
            else
            {
                std::cout << "Please specify the particle data file after using the -i flag" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if(arg == "--display-diagnostics" || arg == "-dd") // will display energy and momentum values in the corner of the screen if true
        {
            m_DisplayDiagnositics == true;
        }
    }

    // Checking for mandatory input
    if(m_NumParticles == 0)
    {
        std::cout << "Please specify number of particles using -n flag" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(!m_ParticleFile.is_open())
    {
        std::cout << "Please specify particle data file using -i flag" << std::endl;
        exit(EXIT_FAILURE);
    }
}

size_t ArgParser::getNumParticles()
{
    return m_NumParticles;
}
double ArgParser::getGravitationalStrength()
{
    return m_GravitationalStrength;
}

double ArgParser::GetTimestep()
{
    return m_Timestep;
}
bool ArgParser::getDisplayDiagnositics()
{
    return m_DisplayDiagnositics;
}