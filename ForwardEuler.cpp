#include <vector>
#include "Integrator.h" // Include the integrator header to link to that abstract class

class ForwardEuler : public Integrator { // create a class that contains the Forward Euler method of solving y(n+1), given y(n)
public: 
    std::vector<double> timeStep( // Contains the equations defining our integration/timescheme method
    const System& systemReference,
    const std::vector<double>& y,
    double t, double dt) const override { // Through overide we make sure that if integrator points to this class, it will be the Forward Euler that is used
        std::vector<double> ODEFunc = systemReference.rhs(y); // Assigns the rhs of the ODE's stored in the system class to ODEFunc
        std::vector<double> ynew(y.size());

        for (unsigned int i = 0; i < y.size(); ++i) { // Loops for size of y to compute each new index
            ynew[i] = y[i] + dt * ODEFunc[i]; // The forward euler first order equation for y(n+1)
        }
        return ynew; // returns ynew when called
    };
};