#include <iostream>
#include <vector>
#include <stdio.h>

bool t1 = true;
bool t2 = true;
bool t3 = true;

std::vector<int> x1 = {0, 0, 0};
std::vector<int> x2 = {0, 0, 0};
std::vector<int> x3 = {0, 0, 0};

std::vector<std::vector<int>> X;

std::vector<int> M_0 = {1, 0, 0, 1};

std::vector<std::vector<int>> B_plus = { {0, 0, 0}, {1, 1, 0}, {1, 0, 1}, {0, 1, 0} };
std::vector<std::vector<int>> B_minus = { {1, 0, 1}, {0, 1, 0}, {0, 1, 0}, {0, 0, 1} };
std::vector<std::vector<int>> B;

std::vector<std::vector<int>> allStates;

void calculateIncidentMatrix();
void calculateNextMarking(std::vector<int> m, std::vector<int> x);
void findFiringTransitions(std::vector<int> m);
void printMatrix(std::string name, std::vector<std::vector<int>> vect);
void formXVector();

int main() {
    allStates.push_back(M_0);

    calculateIncidentMatrix();

    findFiringTransitions(M_0);
    formXVector();
        
    for(int i = 0; i < X.size(); i++) {
        for(int j = 0; j < X[i].size(); j++)
            if(X[i][j] != 0) {
                calculateNextMarking(M_0, X[i]);
                break;
            }
    }

    printMatrix("All States", allStates);

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

void findFiringTransitions(std::vector<int> m) {
    for(int row = 0; row < B.size(); row++)
        for(int column = 0; column < B[row].size(); column++) { 
            if(column == 0) {
                if(m[row] < B_minus[row][column])
                    t1 = false;
                else if(t1 != false)
                    t1 = true;
            }
            else if(column == 1) {
                if(m[row] < B_minus[row][column])
                    t2 = false;
                else if(t2 != false)
                    t2 = true;
            }
            else {
                if(m[row] < B_minus[row][column])
                    t3 = false;
                else if(t3 != false)
                    t3 = true;
            }   
        }
}

void printMatrix(std::string name, std::vector<std::vector<int>> vect) {
    std::cout << "matrix " << name << ": \n";
    for(int row = 0; row < vect.size(); row++) {
        for(int column = 0; column < vect[row].size(); column++) {
            std::cout << vect[row][column] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
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

void formXVector() {   
    if(t1 == true) 
        x1[0] = 1;
    if(t2 == true) 
        x2[1] = 1;
    if(t3 == true)
        x3[2] = 1;

    X.push_back(x1);
    X.push_back(x2);
    X.push_back(x3);
}