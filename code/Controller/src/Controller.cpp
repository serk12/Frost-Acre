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
    Model3D model = ObjManager::readObj(objFile);
    this->parseMaterial();

    SimulatorManager *simMan = new SimulatorManager();
    Instrument *instrument   = new Instrument(material, model);

    Sound sound = simMan->simulateAll(*instrument);

    Debug::print(model);
    Debug::print(*instrument);

    delete instrument;
    delete simMan;
}

void Controller::parseMaterial() {
    rapidjson::Document doc = JsonManager::readFile(jsonFile);

    for (auto& val : doc[JsonManager::MATERIAL.c_str()].GetArray()) {
        Material material;
        material.elasticityK          = val[JsonManager::ELASTICITYK.c_str()].GetDouble();
        material.thicknessT           = val[JsonManager::THICKNESST.c_str()].GetDouble();
        material.youngsModulusY       = val[JsonManager::YOUNGSMODULUSY.c_str()].GetDouble();
        material.densityD             = val[JsonManager::DENSITYD.c_str()].GetDouble();
        material.fluidDampingV        = val[JsonManager::FLUIDDAMPINGV.c_str()].GetDouble();
        material.viscoelasticDampingN = val[JsonManager::VISCOELASTICDAMPINGN.c_str()].GetDouble();

        this->material.push_back(material);
    }
}
