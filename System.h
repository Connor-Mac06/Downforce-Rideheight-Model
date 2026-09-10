#ifndef systemHeader //use guard as its a header file
#define systemHeader
#include <vector>

class System {
public:
    virtual std::vector<double> rhs(const std::vector<double>& y) const = 0;    // Computes RHS of ODE system
    virtual unsigned int numParameters() const = 0; //For returning number of parameters and conditions to filereader()
    virtual unsigned int initConditions() const = 0;
    virtual void setParameters(const std::vector<double>& parameters) = 0; // Set the parameters used by the system
    virtual void setInitConditions(const std::vector<double>& InitConditions) {}; //Not pure virtual as many ODE systems dont require/call this
    virtual ~System() {} //Virtual destructor to allow clean up derived system classes
};

#endif