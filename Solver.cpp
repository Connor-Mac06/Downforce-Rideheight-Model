#include "Solver.h"
void Solver::run() { //The public function to run the private file handling
    FileReader();
    FileOutput();
}
void Solver::FileReader() {
    std::ifstream file("parameters.txt"); //Open parameters file
    if (!file.is_open()) {throw std::runtime_error("Could not open parameters.txt");}
    auto FirstLine = readParsedLine(file); //Reads first line of file as a string

    //Parsing of first line and error handling for certain edge cases
    if (!(FirstLine >> ODE >> TimeScheme >> T >> dt )) {throw std::runtime_error("Missing values in the first line");}
    if (FirstLine >> extraVal) {throw std::runtime_error("Too many values in the first line");}
    if (T <= 0) throw std::runtime_error("T must be greater than 0");
    if (dt <= 0) throw std::runtime_error("dt must be greater than 0");
    if (dt > T) throw std::runtime_error("dt cannot be larger than T");

    switch (ODE) { //Switch for the parameter ODE that tells the system pointer which derived class it should point to depending on user input
        case 0: system = std::make_unique<CoupledOscillators>(); break;
        case 1: system = std::make_unique<CoupledDowforceRideHeight>(); break;
        // Add new systems as cases here
        default:
            throw std::runtime_error("Unknown ODE system: " + std::to_string(ODE));
    }

    //access and call the selected systems functions numParameters() and initConditions() to know how many input parameters to expect
    unsigned int numParam = system->numParameters(); 
    std::vector<double> params(numParam);
    unsigned int numInit = system->initConditions();
    y.resize(numInit);

    auto SecondLine = readParsedLine(file); //Read second line of file
    for (unsigned int i = 0; i < numParam; i++) {
        if (!(SecondLine >> params[i])) {throw std::runtime_error("Not enough parameters for system");} //Fills params with each value fromn file 2nd line, for the number of expected values
    }
    if (SecondLine >> extraVal) {throw std::runtime_error("Too many parameters given");}//Checks for more characters in the line
    system->setParameters(params); // Access system to call setParameters with params input.
    
    auto FinalLine = readParsedLine(file);
    for (unsigned int i = 0; i < numInit; i++) {
        if (!(FinalLine >> y[i])) {throw std::runtime_error("Not enough intial conditions for system");} //Assigns inital conditions in third line to vector y
    }
    if (FinalLine >> extraVal) {throw std::runtime_error("Too many intial conditions given");}
    system->setInitConditions(y); // Access system to call setIniticonditions with y input, so constant initial conditions can be used if required

    switch (TimeScheme) { //Similar to ODE switch except this tells integrator which timescheme to use
        case 0: integrator = std::make_unique<ForwardEuler>();; break;
        case 1: integrator = std::make_unique<RK4>(); break;
        // Add new timeschemes here
        default:
            throw std::runtime_error("Unknown integration scheme:" + std::to_string(TimeScheme));
    }
}
void Solver::FileOutput() {
    std::ostringstream buffer; //Used to reduce disk I/O and improve efficency of writing to buffer

    buffer << t;
    for (double value : y) {buffer << " " << value;} //Writes the initial state to buffer
    buffer << "\n";

    while (t < T) {
        double dtAdjusted = std::min(dt, T - t); // Although most of the iterations will use dt, this ensures that if the remaining gap is less it will use what remains
        y = integrator->timeStep(*system, y, t, dtAdjusted); //Calls the chose timescheme method on the latest and reassigns to a new y
        t += dtAdjusted; //Increases the total time with each timestep
        buffer << t; //Writes each new state as a new line in buffer
        for (double value : y) {buffer << " " << value;}
        buffer << "\n";
    }
    std::ofstream out("output.txt"); //Output buffer as a file Output.txt
    out << buffer.str();
}
std::istringstream Solver::readParsedLine(std::ifstream& file){ //function for parsing line until new line
    std::string line; // creates a string line that is assigned with get line  which only reads one line
    if (!std::getline(file, line)) {throw std::runtime_error("Unexpected end of file while reading parameters.");}
    return std::istringstream(line);
}