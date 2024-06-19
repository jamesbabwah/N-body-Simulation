#ifndef ARGPARSER_HPP
#define ARGPARSER_HPP

#include <cstdlib>
#include <string>
#include <fstream>


class ArgParser
{
public:
    ArgParser(int argc, char* argv[]);

    size_t getNumParticles();
    double getGravitationalStrength();
    double GetTimestep();
    bool   getDisplayDiagnositics();

private:
    size_t        m_NumParticles = 0;                      //Number of bodies in simulation
    double        m_GravitationalStrength = 3.3707e-20;    //Gravitational Field strength
    double        m_Timestep = 1.15741e-5;                 //Timestep to be used between frames
    bool          m_DisplayDiagnositics = false;           //Display Energy and Momentum values on screen
    std::ifstream m_ParticleFile;                          //File containing inital data of particles
};

#endif //ARGPARSER_HPP