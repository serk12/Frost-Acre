#include <iostream>
#include <Eigen/Dense>

#include "header/SimulatorManager.h"
#include "header/String.h"
#include "header/Utils.h"
#include "header/Instrument.h"

int main() {
    Model3D model;
    model.vertex       = Eigen::MatrixXd(2, 4);
    model.vertex(0, 0) = 2.0f;
    model.vertex(0, 1) = 2.0f;
    model.vertex(0, 2) = 2.0f;
    model.vertex(0, 3) = 2.0f;
    model.edge         = Eigen::MatrixXd(2, 2);
    model.edge(0, 0)   = 0;
    model.edge(0, 1)   = 1;
    model.edge(1, 0)   = 1;
    model.edge(1, 1)   = 0;
    Instrument *instrument   = new Instrument();
    String     *string       = new String(model);
    SimulatorManager *simMan = new SimulatorManager();

    Sound sound = simMan->simulateAll(*string, *instrument);

    delete simMan;
    delete string;
}
