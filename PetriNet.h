#ifndef PETRINET_H
#define PETRINET_H

#include <iostream>
#include <vector>

class PetriNet {

    private:
        std::vector<bool> transitions;
        std::vector<std::vector<int>> X;
        std::vector<int> M_0;
        std::vector<std::vector<int>> B_plus;
        std::vector<std::vector<int>> B_minus;
        std::vector<std::vector<int>> B_controller_minus;
        std::vector<std::vector<int>> B;
        std::vector<std::vector<int>> L;
        std::vector<int> M_C_0;
        std::vector<int> b;
        std::vector<std::vector<int>> B_controller;
        std::vector<std::vector<int>> allStates;

    public:
        PetriNet();
        void start();

        // Calculation functions
        void calculateIncidentMatrix();
        void calculateNextMarking(std::vector<int>, std::vector<int>);
        void calculateControllerIncidentMatrix();
        void calculcateControllerZeroMarking();

        // Core functions
        void setControllerIncidentAndMarkingMatriciesSizes(int x, int y, int t);
        void findFiringTransitions(std::vector<int> m);
        void findAllStatesFromInitialMarking();
        void formXVector();
        void formTransitionsVector();
        void clearXVectorAndFiringStates();

        // Printing functions
        void printMatrix(std::string name, std::vector<int> vect);
        void print2DMatrix(std::string name, std::vector<std::vector<int>> vect);
        void printAllStates();
};

#endif