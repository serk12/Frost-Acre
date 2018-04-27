#include <iostream>
#include <Eigen/Dense>

#include "SimulatorBundle/header/SimulatorManager.h"
#include "SimulatorBundle/header/Instrument.h"
#include "DebugUtils.h"

#include "InputBundle/header/ObjManager.h"
#include "InputBundle/header/JsonManager.h"

int main() {
    Model3D model           = ObjManager::readObj("./test/cube.obj");
    rapidjson::Document doc = JsonManager::readFile("./test/cube.json");
    JsonManager::writeFile("./test/cube.json", doc);
    Instrument *instrument =
        new Instrument(doc[JsonManager::ELASTICITYK.c_str()].GetDouble(),
                       doc[JsonManager::THICKNESST.c_str()].GetDouble(),
                       doc[JsonManager::YOUNGSMODULUSY.c_str()].GetDouble(),
                       doc[JsonManager::DENSITYD.c_str()].GetDouble(),
                       doc[JsonManager::FLUIDDAMPINGV.c_str()].GetDouble(),
                       doc[JsonManager::VISCOELASTICDAMPINGN.c_str()].GetDouble(),
                       model);
    SimulatorManager *simMan = new SimulatorManager();

    Sound sound = simMan->simulateAll(*instrument);

    Debug::print(model);
    Debug::print(*instrument);

    delete instrument;
    delete simMan;
}
