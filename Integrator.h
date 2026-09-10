#ifndef integratorHeader //use guards as its a header file
#define integratorHeader
#include <vector>
#include "System.h"

class Integrator {
public:
    virtual std::vector<double> timeStep( //Returns updated vector after each tintegration time step
        const System& systemReference, //reference to system class containing ODES
        const std::vector<double>& y, //declare vector y and other variables
        double t, double dt) const = 0;
    virtual ~Integrator() {} //Virtual destructor to allow clean up derived intergator classes
};

#endif