Omar Abdelalim
12/10/2021

This program prints all of the possible reachable states given a petri net model.

Program's Manual Requirement: 
1- A manual input of matrix M_0, which is the initial marking of the initial petri net
2- A manual input of matrix B_minus and B_plus of the initial uncontrolled petri net
3- A manual input of matrix L which defines the desired controlling behavior
4- A manual input of matrix b
5- A manual input of matrix B_controller_minus of the controlled petri net

Program's Output:
1- The initial marking of the controlled petri net
2- The incident matrix of the controlled petri net
3- All of the possible reachable states from the initial marking of the controlled petri net

How To Run The Program:
1- Go to tesla.cs.iupui.edu or any other linux terminal that has C++ and gdb installed. 
2- Type make run, the program will then compile and run all in one step

Notes on compiling:
The program must be compiled using C++11 or any new version, the makefile already ensures that. Otherwise, it might complain about 2D vector notations.