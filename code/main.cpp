#include <iostream>
#include <Eigen/Dense>

#include "header/SimulatorManager.h"
#include "header/String.h"
#include "header/Utils.h"

int main() {
    Model3D model;

    String *string           = new String(model);
    SimulatorManager *simMan = new SimulatorManager();

    Sound sound = simMan->simulateAll(*string);
    delete string;
    delete simMan;
}
