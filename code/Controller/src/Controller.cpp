#include "../header/Controller.h"

Controller::Controller() {}

Controller::Controller(std::string objFile, std::string jsonFile)
    : Controller() {
    this->objFile  = objFile;
    this->jsonFile = jsonFile;
}

void Controller::setObjFile(std::string objFile) {
    this->objFile = objFile;
}

void Controller::setjsonFile(std::string jsonFile) {
    this->jsonFile = jsonFile;
}

void Controller::run() {
    Model3D model           = ObjManager::readObj(objFile);
    rapidjson::Document doc = JsonManager::readFile(jsonFile);
    Material material;
    material.elasticityK          = doc[JsonManager::ELASTICITYK.c_str()].GetDouble();
    material.thicknessT           = doc[JsonManager::THICKNESST.c_str()].GetDouble();
    material.youngsModulusY       = doc[JsonManager::YOUNGSMODULUSY.c_str()].GetDouble();
    material.densityD             = doc[JsonManager::DENSITYD.c_str()].GetDouble();
    material.fluidDampingV        = doc[JsonManager::FLUIDDAMPINGV.c_str()].GetDouble();
    material.viscoelasticDampingN = doc[JsonManager::VISCOELASTICDAMPINGN.c_str()].GetDouble();

    materials.push_back(material);

    SimulatorManager *simMan = new SimulatorManager();
    Instrument *instrument   = new Instrument(materials, model);

    Sound sound = simMan->simulateAll(*instrument);

    Debug::print(model);
    Debug::print(*instrument);

    delete instrument;
    delete simMan;
}

void Controller::parseMaterial() {}
