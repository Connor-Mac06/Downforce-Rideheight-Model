#include <vector>
#include "System.h" // Include the system header to link to that abstract class

class CoupledOscillators : public System { // create a class that contains the Coupled Oscillations system of equations, for holding the calculations required in the timeschemes
public:
    void setParameters(const std::vector<double>& parameters) override { //Uses the array passed to it from solver class to create vector parameters
        Mass1 = parameters[0];// Then assigns the value of each vector index to the relevant variable
        Mass2 = parameters[1];// These parameters effect how the masses interact with each other
        k1 = parameters[2]; //Spring constants
        k2 = parameters[3];
        k3 = parameters[4];
    }

    std::vector<double> rhs(const std::vector<double>& y) const override { // contains the instructions on what to do with our input conditions (y) to calculate the ODE value for that (y)
        double x1 = y[0]; //displacement 1   //indexes vector y to access initial conditions
        double v1 = y[1]; //velocity 1
        double x2 = y[2]; //displacement 2
        double v2 = y[3]; //velocity  2

        std::vector<double> derivativeValue(4); // Creates a vector derivativeValue, in which we then store the solution of the 4 ODES's that make up this system of equations
        derivativeValue[0] = v1;
        derivativeValue[1] = (-k1*x1 - k2*(x1 - x2)) / Mass1;
        derivativeValue[2] = v2;
        derivativeValue[3] = (-k3*x2 - k2*(x2 - x1)) / Mass2;

        return derivativeValue; // returns this vector when called
    }
    unsigned int numParameters() const override {return 5;} // These contain the number of parameters and inital conditions expected, so that we can tell the solver class, and fileReader() knows how many inputs to expect
    unsigned int initConditions() const override {return 4;}
private:  // The private component of the class is used for declaration of all variables unique to this class.
    double Mass1, Mass2, k1, k2, k3;
};