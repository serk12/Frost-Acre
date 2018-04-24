#include <iostream>
#include <Eigen/Dense>

#include "SimulatorBundle/header/SimulatorManager.h"
#include "SimulatorBundle/header/Instrument.h"
#include "SimulatorBundle/header/String.h"
#include "DebugUtils.h"

#include "InputBundle/header/ObjManager.h"

int main() {
    Model3D model = ObjManager::readObj("./test/cube.obj");

    Instrument *instrument   = new Instrument();
    String     *string       = new String(model);
    SimulatorManager *simMan = new SimulatorManager();

    Sound sound = simMan->simulateAll(*string, *instrument);

    delete simMan;
    delete string;
}
