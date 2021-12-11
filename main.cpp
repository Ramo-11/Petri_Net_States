#include <iostream>
#include <vector>
#include <stdio.h>

std::vector<bool> transitions;

std::vector<std::vector<int>> X;

std::vector<int> M_0 = {0, 1, 0, 0, 0, 0, 1, 0};

std::vector<std::vector<int>> B_plus = { 
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1}
};
std::vector<std::vector<int>> B_minus = { 
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}
 };

std::vector<std::vector<int>> B_controller_minus = { 
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1}
 };

std::vector<std::vector<int>> B;

std::vector<std::vector<int>> L = { 
    {1, 0, 0, 0, 1, 0, 0, 0}, 
    {0, 1, 0, 0, 0, 1, 0, 0}, 
    {0, 0, 1, 0, 0, 0, 1, 0}, 
    {0, 0, 0, 1, 0, 0, 0, 1}
};

std::vector<int> M_C_0;

std::vector<int> b = {1, 1, 1, 1};

std::vector<std::vector<int>> B_controller;

std::vector<std::vector<int>> allStates;

// Uses B+ and B- to find B
void calculateIncidentMatrix();

// Takes a marking state, and the x transition vector, and uses them to find the next marking
// using the formula M(k+1) = M(k) + B*x
void calculateNextMarking(std::vector<int> m, std::vector<int> x);

void calculateControllerIncidentMatrix();

void calculcateControllerZeroMarking();

// Takes a marking state, and calculates if firing happens or not by comparing it
// with every column in B-
void findFiringTransitions(std::vector<int> m);

void findAllStatesFromInitialMarking();

// Forms x1, x2, .., xn, which are all stored in matrix X
void formXVector();

void formTransitionsVector();

void clearXVectorAndFiringStates();

// Takes the name of the 2d matrix and prints it 
void printMatrix(std::string name, std::vector<int> vect);

void print2DMatrix(std::string name, std::vector<std::vector<int>> vect);

void printAllStates();

void setControllerIncidentAndMarkingMatriciesSizes(int x, int y, int t);


int main() {
    calculateIncidentMatrix();
    calculateControllerIncidentMatrix();
    calculcateControllerZeroMarking();

    printMatrix("Petri Net Initial Marking", M_C_0);
    print2DMatrix("Petri Net incident Matrix", B_controller);

    allStates.push_back(M_C_0);
    findAllStatesFromInitialMarking();

    printAllStates();

    return 0;
}

void calculateIncidentMatrix() {
    std::vector<int> temp;
    for(int row = 0; row < B_plus.size(); row++) {
        for(int column = 0; column < B_plus[row].size(); column++)
            temp.push_back(B_plus[row][column] - B_minus[row][column]);
        B.push_back(temp);
        temp.clear();
    }
}

void calculateControllerIncidentMatrix() {
    setControllerIncidentAndMarkingMatriciesSizes(12, 12, 12);

    for(int i = 0; i < L.size(); i++)
        for(int j = 0; j < B[i].size(); j++)
            for(int k = 0; k < B.size(); k++)
                B_controller[i+8][j] += -1 * (L[i][k] * B[k][j]);

    int k = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 12; j++)
            B_controller[i][j] = B[k][j];
        k++;
    }
}

void calculcateControllerZeroMarking() {
    std::vector<std::vector<int>> temp = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0} };
    for(int i = 0; i < L.size(); i++) {
        for(int j = 0; j < 1; j++) {
            for(int k = 0; k < M_0.size(); k++)
                temp[i][j] += (L[i][k] * M_0[k]);
        }
    }

    for(int i = 0; i < 4; i++)
        M_C_0[i+8] = b[i] - temp[i][0];

    for(int i = 0; i < 8; i++)
        M_C_0[i] = M_0[i];
}

void findAllStatesFromInitialMarking() {
    formTransitionsVector();

    for(int k = 0; k < allStates.size(); k++) {
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
}

void formTransitionsVector() {
    for(int i = 0; i < 12; i++)
        transitions.push_back(true);
}

void findFiringTransitions(std::vector<int> m) {
    for(int column = 0; column < B_controller_minus.size(); column++)
        for(int row = 0; row < B_controller_minus[column].size(); row++) { 
            if(m[row] < B_controller_minus[row][column])
                transitions[column] = false;
            else if(transitions[column] != false)
                transitions[column] = true;
        }
}

void formXVector() {
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

void calculateNextMarking(std::vector<int> m, std::vector<int> x) {
    std::vector<int> temp;
    std::vector<int> temp2;
    int value = 0;
    int flag = 0;

    for(int row = 0; row < B_controller.size(); row++) {
        for(int column = 0; column < B_controller[row].size(); column++) 
            temp.push_back(B_controller[row][column] * x[column]);
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

void clearXVectorAndFiringStates() {
    X.clear();

    for(int i = 0; i < transitions.size(); i++)
        transitions[i] = true;
}

void print2DMatrix(std::string name, std::vector<std::vector<int>> vect) {
    std::cout << "\nmatrix " << name << ": \n";

    for(int row = 0; row < vect.size(); row++) {
        for(int column = 0; column < vect[row].size(); column++)
            std::cout << vect[row][column] << "   ";
        std::cout << "\n";
    }
    std::cout << "\n";
}

void printMatrix(std::string name, std::vector<int> vect) {
    std::cout << "\nmatrix: " << name << ": \n";

    for(int i = 0; i < vect.size(); i++)
        std::cout << vect[i] << " ";

    std::cout << std::endl;
}

void printAllStates() {
    for(int row = 0; row < allStates.size(); row++) {
        std::cout << "\n\nstate " << row + 1 << ": ";
        for(int column = 0; column < allStates[row].size(); column++)
            std::cout << allStates[row][column] << " ";
    }

    std::cout << "\n";
}

void setControllerIncidentAndMarkingMatriciesSizes(int x, int y, int t) {
    B_controller.resize(x);

    for(int i = 0; i < x; i++)
        B_controller[i].resize(y);

    M_C_0.resize(t);
}