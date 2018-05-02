#include <iostream>
#include <Eigen/Dense>
#include <vector>

#include "SimulatorBundle/header/SimulatorManager.h"
#include "SimulatorBundle/header/Instrument.h"
#include "DebugUtils.h"

#include "InputBundle/header/ObjManager.h"
#include "InputBundle/header/JsonManager.h"

int main() {
    Model3D model             = ObjManager::readObj("./test/cube/cube.obj");
    rapidjson::Document   doc = JsonManager::readFile("./test/cube/cube.json");
    std::vector<Material> materials(1);

    materials[0].elasticityK          = doc[JsonManager::ELASTICITYK.c_str()].GetDouble();
    materials[0].thicknessT           = doc[JsonManager::THICKNESST.c_str()].GetDouble();
    materials[0].youngsModulusY       = doc[JsonManager::YOUNGSMODULUSY.c_str()].GetDouble();
    materials[0].densityD             = doc[JsonManager::DENSITYD.c_str()].GetDouble();
    materials[0].fluidDampingV        = doc[JsonManager::FLUIDDAMPINGV.c_str()].GetDouble();
    materials[0].viscoelasticDampingN = doc[JsonManager::VISCOELASTICDAMPINGN.c_str()].GetDouble();

    SimulatorManager *simMan = new SimulatorManager();
    Instrument *instrument   = new Instrument(materials, model);

    Sound sound = simMan->simulateAll(*instrument);

    Debug::print(model);
    Debug::print(*instrument);

    delete instrument;
    delete simMan;
}
