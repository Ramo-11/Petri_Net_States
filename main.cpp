#include <iostream>
#include <vector>
#include <stdio.h>

bool t1 = true;
bool t2 = true;
bool t3 = true;

std::vector<bool> transitions;

std::vector<std::vector<int>> X;

std::vector<int> M_0 = {1, 0, 0, 1};

std::vector<std::vector<int>> B_plus = { {0, 0, 0}, {1, 1, 0}, {1, 0, 1}, {0, 1, 0} };
std::vector<std::vector<int>> B_minus = { {1, 0, 1}, {0, 1, 0}, {0, 1, 0}, {0, 0, 1} };
std::vector<std::vector<int>> B;

std::vector<std::vector<int>> allStates;

// Uses B+ and B- to find B
void calculateIncidentMatrix();

// Takes a marking state, and the x transition vector, and uses them to find the next marking
// using the formula M(k+1) = M(k) + B*x
void calculateNextMarking(std::vector<int> m, std::vector<int> x);

// Takes a marking state, and calculates if firing happens or not by comparing it
// with every column in B-
void findFiringTransitions(std::vector<int> m);

void findAllStatesFromInitialMarking();

// Forms x1, x2, .., xn, which are all stored in matrix X
void formXVector();

void formTransitionsVector();

void clearXVectorAndFiringStates();

// Takes the name of the 2d matrix and prints it 
void printMatrix(std::string name, std::vector<std::vector<int>> vect);

void printAllStates();


int main() {
    allStates.push_back(M_0);

    calculateIncidentMatrix();

    findAllStatesFromInitialMarking();

    printAllStates();

    return 0;
}


void calculateIncidentMatrix() {
    std::vector<int> temp;
    for(int row = 0; row < B_plus.size(); row++) {
        for(int column = 0; column < B_plus[row].size(); column++) {
            temp.push_back(B_plus[row][column] - B_minus[row][column]);
        }
        B.push_back(temp);
        temp.clear();
    }

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
    transitions.push_back(t1);
    transitions.push_back(t2);
    transitions.push_back(t3);
}

void findFiringTransitions(std::vector<int> m) {
    for(int column = 0; column < B_minus.size(); column++)
        for(int row = 0; row < B_minus[column].size(); row++) { 
            if(m[row] < B_minus[row][column])
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
    }
}

void calculateNextMarking(std::vector<int> m, std::vector<int> x) {
    std::vector<int> temp;
    std::vector<int> temp2;
    int value = 0;

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

    allStates.push_back(newMarking);  
}

void clearXVectorAndFiringStates() {
    X.clear();

    for(int i = 0; i < transitions.size(); i++)
        transitions[i] = true;
}

void printMatrix(std::string name, std::vector<std::vector<int>> vect) {
    std::cout << "matrix " << name << ": \n";
    for(int row = 0; row < vect.size(); row++) {
        for(int column = 0; column < vect[row].size(); column++)
            std::cout << vect[row][column] << " ";
        std::cout << "\n";
    }
    std::cout << "\n";
}

void printAllStates() {
    for(int row = 0; row < allStates.size(); row++) {
        std::cout << "\n\nstate " << row + 1 << ": ";
        for(int column = 0; column < allStates[row].size(); column++)
            std::cout << allStates[row][column] << " ";
    }

    std::cout << "\n";
}