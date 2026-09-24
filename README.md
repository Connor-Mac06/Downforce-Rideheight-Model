The first step to running the solver is simply entering the following into the terminal for the working
directory:

g++ -Wall -Wpedantic -std=c++17 *.cpp

This will create an executable a.out, which will automatically read parameters.txt from the work-
ing directory and can be executed with:
./a.out

The executable will then output the solution to the selected system in a separate file, output.txt,
which will appear within the same directory.

1.2 Parameters

The only other file required to run this solver is parameters.txt, which holds all the input param-
eters and user selections needed to use this solver. It is formatted in the following way:

[ODE] [TimeScheme] [T] [dt]
[param1] [param2] ... [paramM]
[ic0] [ic1] ... [icN]

1.2.1 ODE System Selection

The first parameter, [ODE], decides which system of equations the user would like to solve. There
are two possible inputs:

0: Chooses the Coupled Oscillators System; a system of two masses connected by 3 springs.
1: Chooses the Coupled Aerodynamic Suspension System; a system of downforce acting on a
vehicle of constant speed and variable ride height.

The next parameter, [TimeScheme], decides which time scheme to solve the ODE with. There are
again two possible inputs:
0: Solve the system using Forward Euler (Less accurate but uses less computational cost).
1: Solve system with Fourth-Order Runge-Kutta (More accurate but greater computational cost)

The two remaining parameters on this line, [T] and [dt], take the total range of time to solve, and
the size of the timestep to use, respectively. For both systems used within this solver, the parameters
are expressed in seconds. However, future systems may require other time units.

1.2.2 Time Scheme Selection and Time Parameters
The next line of parameters.txt holds the input parameters for the ODE system itself. For the Cou-
pled Oscillators System, there are five input parameters:

Mass1: The mass of the first component in kg
Mass2: The mass of the second component in kg
k1: The stiffness constant of the first spring in N/m
k2: The stiffness constant of the second spring in N/m
k3: The stiffness constant of the third spring in N/m

For the Coupled Aerodynamic Suspension System, there are four input parameters:

Mass: The mass of the formula student car in kg
Damping: The damping constant of the car shocks and tyres in N s/m
ConstantVelocity: The forward velocity of the car in m/s
SuspensionStiffness: The stiffness constant of the car shocks and tyres in N/m

1.2.3 Input Parameters and Initial Conditions

The final line of parameters.txt holds the initial conditions of the ODE system. For the Coupled
Oscillators System there are four input parameters:

x1: The initial displacement of the first mass in m
v1: The initial velocity of the first mass in m/s
x2: The initial displacement of the first mass in m
v2: The initial velocity of the second mass in m/s

For the Coupled Aerodynamic Suspension System, there are two input parameters:
Height: The distance from the car to ground when it is static in m
VerticalVelocity: The vertical velocity of car body when its forward motion is static in m/s

1.2.4 Solver Output
The results are outputted into a file output.txt in the form Where there is a new line for each
timestep taken. These results can be plotted through MATLAB for a graph of how the initial conditions
change with time
