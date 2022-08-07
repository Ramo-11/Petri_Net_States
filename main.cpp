#include "PetriNet.h"

int main() {
    PetriNet model;

    model.start();
    model.findAllStatesFromInitialMarking();
    model.printAllStates();

    return 0;
}