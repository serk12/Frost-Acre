#include <iostream>
#include <Eigen/Dense>

#include "SimulatorBundle/header/SimulatorManager.h"
#include "SimulatorBundle/header/Instrument.h"
#include "DebugUtils.h"

#include "InputBundle/header/ObjManager.h"

int main() {
    Model3D model = ObjManager::readObj("./test/cube.obj");
    Debug::print(model);
    Instrument *instrument   = new Instrument(model);
    SimulatorManager *simMan = new SimulatorManager();

    Sound sound = simMan->simulateAll(*instrument);

    delete instrument;
    delete simMan;
}
