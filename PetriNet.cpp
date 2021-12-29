#include "PetriNet.h"

PetriNet::PetriNet() {
    initialMarking = {0, 1, 0, 0, 0, 0, 1, 0};
    B_plus = { 
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1}
    };
    B_minus = { 
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}
    };
    allStates.push_back(initialMarking);
}

void PetriNet::findAllStatesFromInitialMarking() {
    calculateIncidentMatrix();
    
    formTransitionsVector();

    for(int k = 0; k < allStates.size(); k++) {
        std::cout << "k: " << k << "\n";
        findFiringTransitions(allStates[k]);
        formXVector();
        for(int i = 0; i < X.size(); i++) {
            for(int j = 0; j < X[i].size(); j++)
                if(X[i][j] != 0) {
                    calculateNextMarking(allStates[k], X[i]);
                    break;
                }
        }

        clearXVectorAndFiringStates();
    }

    printAllStates();
}

void PetriNet::calculateIncidentMatrix() {
    std::vector<int> temp;
    for(int row = 0; row < B_plus.size(); row++) {
        for(int column = 0; column < B_plus[row].size(); column++)
            temp.push_back(B_plus[row][column] - B_minus[row][column]);
        B.push_back(temp);
        temp.clear();
    }
}

void PetriNet::formTransitionsVector() {
    for(int i = 0; i < 12; i++)
        transitions.push_back(true);
}

void PetriNet::findFiringTransitions(std::vector<int> m) {
    for(int column = 0; column < B_minus[0].size(); column++)
        for(int row = 0; row < B_minus.size(); row++) { 
            if(m[row] < B_minus[row][column])
                transitions[column] = false;
            else if(transitions[column] != false)
                transitions[column] = true;
        }
}

void PetriNet::formXVector() {
    std::vector<int> tempX;

    for(int i = 0; i < transitions.size(); i++) {
        tempX.push_back(0);
    }

    for(int i = 0; i < transitions.size(); i++) {
        if(transitions[i] == true)
            tempX[i] = 1;
        else
            for(int j = 0; j < tempX.size(); j++)
                tempX[j] = 0;
        X.push_back(tempX);

        for(int k = 0; k < tempX.size(); k++)
            tempX[k] = 0;
    }
}

void PetriNet::calculateNextMarking(std::vector<int> m, std::vector<int> x) {
    std::vector<int> temp;
    std::vector<int> temp2;
    int value = 0;
    int flag = 0;

    for(int row = 0; row < B.size(); row++) {
        for(int column = 0; column < B[row].size(); column++) 
            temp.push_back(B[row][column] * x[column]);
        for(int i = 0; i < temp.size(); i++)
            value += temp[i];

        temp2.push_back(value);
        temp.clear();
        value = 0;
    }

    std::vector<int> newMarking;

    for(int i = 0; i < temp2.size(); i++) 
        newMarking.push_back(m[i] + temp2[i]);  

    // Checks if this is a duplicate marking
    for(int i = 0; i < allStates.size(); i++)
        if(newMarking == allStates[i])
            flag = 1;

    if(flag != 1)
        allStates.push_back(newMarking); 
}

void PetriNet::clearXVectorAndFiringStates() {
    X.clear();

    for(int i = 0; i < transitions.size(); i++)
        transitions[i] = true;
}

void PetriNet::printAllStates() {
    for(int row = 0; row < allStates.size(); row++) {
        std::cout << "\n\nstate " << row + 1 << ": ";
        for(int column = 0; column < allStates[row].size(); column++)
            std::cout << allStates[row][column] << " ";
    }

    std::cout << "\n";
}