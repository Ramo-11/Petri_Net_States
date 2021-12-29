#ifndef PETRINET_H
#define PETRINET_H

#include <iostream>
#include <vector>

class PetriNet {

    private:
        std::vector<bool> transitions;
        std::vector<std::vector<int>> X;
        std::vector<int> initialMarking;
        std::vector<std::vector<int>> B_plus;
        std::vector<std::vector<int>> B_minus;
        std::vector<std::vector<int>> B;
        std::vector<std::vector<int>> allStates;

    public:
        PetriNet();

        void calculateIncidentMatrix();
        void findAllStatesFromInitialMarking();
        void formTransitionsVector();
        void findFiringTransitions(std::vector<int>);
        void formXVector();
        void calculateNextMarking(std::vector<int>, std::vector<int>);
        void printAllStates();
        void clearXVectorAndFiringStates();
};

#endif