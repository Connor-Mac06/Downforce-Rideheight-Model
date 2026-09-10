#include <vector>
#include <math.h>
#include "System.h" // include the header file of system

class CoupledDowforceRideHeight : public System { // create a class that contains the Coupled Aerodynamic Suspension system of equations, and can be used for calculations required in the timeschemes
public:
    void setParameters(const std::vector<double>& parameters) override { // Uses the array passed to it from solver class to create vector parameters
        Mass = parameters[0]; // weight of car (kg)                     // Then assigns the value of each vector index to the relevant variable
        Damping = parameters[1]; // Shock & Tyre Damping (Ns/m)        //These parameters effect the bahaviour of the car motion
        ConstantVelocity = parameters[2]; // forward velocity of the car (m/s)
        SuspensionStiffness = parameters[3]; // (N/m))
    }
    void setInitConditions(const std::vector<double>& InitConditions) override {NominalRideHeight = InitConditions[0];} //This is specifically for assigning an initial condition input parameter which we dont want to change in calculations

    // The next part is a group of functions to simplify the creation of a complex downforce function that is part of one of the ODE's.
    // They have been made inline to reduce overhead calculations
    inline double DownforcePre(double h) const{
        double hSafe = std::max(h, 1e-4); //Ensures h (height) cant be 0 or below, to remove unrealistic scenarios and calculation errors
        return 0.5 * AirDensity * ConstantVelocity * ConstantVelocity * UnderFloorArea * CL0 * std::exp(-Alpha * hSafe) + AeroScalingFactor / std::pow(hSafe + Offset, NearGroundExponent);
    }
    inline double DownforcePost(double h) const {
        return postStallFraction * DownforcePre(h);
    }
    inline double BlendFactor(double h) const {
        return 0.5 * (1.0 - std::tanh(StallSharpness * (h - StallHeight)));
    }
    inline double Downforce(double h) const {
        double B = BlendFactor(h);
        return DownforcePre(h) * B + DownforcePost(h) * (1.0 - B);
    }
    
    std::vector<double> rhs(const std::vector<double>& y) const override { // contains the instructions on what to do with our input conditions (y) to calculate the ODE value for that (y)
        double Height = y[0]; // assigns the inital condition vector y to seperate variables
        double VerticalVelocity = y[1];

        std::vector<double> derivativeValue(2); // Creates a vector derivativeValue, in which we then store the solution of the two ODES's that amke up the system
        derivativeValue[0] = VerticalVelocity;
        derivativeValue[1] = -Gravity + Downforce(Height)/Mass - SuspensionStiffness/Mass*(Height-NominalRideHeight) - Damping/Mass * VerticalVelocity;

        return derivativeValue; // returns this vector when called
    }
    unsigned int initConditions() const override {return 2;} // These contain the number of parameters and inital conditions expected, so that we can tell the solver class, and fileReader() knows how many inputs to expect
    unsigned int numParameters() const override {return 4;}
private: // The private component of the class is used for declaration of all variables unique to this class.
    double Height, VerticalVelocity, Mass, NominalRideHeight, Damping, ConstantVelocity, SuspensionStiffness; 
    // Values that will not be altered later are declared as constants (const)
    const double Gravity = 9.81;
    const double AirDensity = 1.225;
    const double UnderFloorArea = 0.6;
    const double AeroScalingFactor = 3.3;
    const double CL0 = 0.5;
    const double Offset = 0.01;
    const double Alpha = 15;
    const double NearGroundExponent = 2;
    const double StallHeight = 0.03;
    const double StallSharpness = 100;
    const double postStallFraction = 0.35;
};