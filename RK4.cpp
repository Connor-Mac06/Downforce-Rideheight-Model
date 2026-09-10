#include <vector>
#include "Integrator.h" // Include the integrator header to link to that abstract class

class RK4   : public Integrator { // create a class that contains the RK4 timescheme method of solving y(n+1), given y(n)
    public: 
      std::vector<double> timeStep( // Contains the equations defining our integration/timescheme method
        const System& systemReference,
        const std::vector<double>& y,
        double t, double dt) const override { // Through override we make sure that if integrator points to this class, it will be the RK4 timescheme that is used
            const unsigned int n = y.size();
            std::vector<double> k1 = systemReference.rhs(y); // Assigns the rhs of the ODE's stored in the system class to k1, the first variable of RK4.
            std::vector<double> y2(n); //Initializing vectors for RK4
            std::vector<double> y3(n);
            std::vector<double> y4(n);
            std::vector<double> ynew(n);

            //The following loops calculate the k1,k2,k3 and k4 for each index of y
            for (unsigned int i = 0; i < n; ++i) {
                y2[i] = y[i] + dt * k1[i] * 0.5;
            }
            std::vector<double> k2 = systemReference.rhs(y2); // Calls rhs function of ODE system class using an input y2
            for (unsigned int i = 0; i < n; ++i) {
                y3[i] = y[i] + dt * k2[i] * 0.5;
            }
            std::vector<double> k3 = systemReference.rhs(y3);
            for (unsigned int i = 0; i < n; ++i) {
                y4[i] = y[i] + dt * k3[i];
            }
            std::vector<double> k4 = systemReference.rhs(y4);       
            for (unsigned int i = 0; i < n; ++i) {
                ynew[i] = y[i] + dt * (k1[i] + 2*k2[i] + 2*k3[i] + k4[i])/6;
            }

            return ynew; // returns ynew when called
        };
};