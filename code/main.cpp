#include <iostream>
#include <Eigen/Dense>

#include "SimulatorBundle/header/SimulatorManager.h"
#include "SimulatorBundle/header/Instrument.h"
#include "SimulatorBundle/header/String.h"
#include "Utils.h"

int main() {
    Model3D model;
    model.vertex       = Eigen::MatrixXd(3, 2);
    model.vertex(0, 0) = 12.32;
    model.vertex(0, 1) = 12.32;
    model.vertex(0, 2) = 12.32;
    model.vertex(1, 0) = 3.21;
    model.vertex(1, 1) = 3.21;
    model.vertex(1, 2) = 3.21;
    model.edge         = MatrixXB(2, 2);
    model.edge(0, 0)   = true;
    model.edge(0, 1)   = true;
    model.edge(1, 0)   = true;
    model.edge(1, 1)   = false;
    Instrument *instrument   = new Instrument();
    String     *string       = new String(model);
    SimulatorManager *simMan = new SimulatorManager();

    Sound sound = simMan->simulateAll(*string, *instrument);

    delete simMan;
    delete string;
}
