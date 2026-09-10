#ifndef SolverHeader //use guard as its a header file
#define SolverHeader

#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
//Include all other files
#include "Integrator.h"
#include "System.h"
#include "ForwardEuler.cpp"
#include "RK4.cpp"
#include "coupledOscillators.cpp"
#include "coupledDownforceHeight.cpp" 

class Solver {
public:
    void run(); //Declares run() as a public functions
private:
    //Declares private variables used in solver
    double t = 0.0; 
    unsigned int ODE, TimeScheme;
    double T, dt, extraVal;
    // creates vector y and unique pointers for system and integrator
    std::vector<double> y; 
    std::unique_ptr<System> system;
    std::unique_ptr<Integrator> integrator;
    //Declares private functions used in solver
    void FileReader(); 
    void FileOutput();
    std::istringstream readParsedLine(std::ifstream& file);
};

#endif