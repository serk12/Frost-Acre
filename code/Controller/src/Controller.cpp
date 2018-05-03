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
    DebugController::startClock();

    DebugController::print("INIT RUN");
    DebugController::print("INIT PARSE");
    Model3D model = ObjManager::readObj(objFile);
    this->parseMaterial();
    DebugController::print("END PARSE");

    SimulatorManager *simMan = new SimulatorManager();
    Instrument *instrument   = new Instrument(material, model);

    DebugController::print("INIT PRECAll");
    simMan->precallSimulator(*instrument);

    Eigen::VectorXd f(24);
    f(0) = 1; f(1)  = 0; f(2)  = 0.2;
    f(3) = 2; f(4)  = 0; f(5)  = 0.4;
    f(6) = 1; f(7)  = 0; f(8)  = 0.3;
    f(9) = 3; f(10) = 0; f(11) = 0.1;

    f(12) = 1; f(13) = 0; f(14) = 0.2;
    f(15) = 2; f(16) = 0; f(17) = 0.4;
    f(18) = 1; f(19) = 0; f(20) = 0.3;
    f(21) = 3; f(22) = 0; f(23) = 0.1;

    DebugController::print("INIT FRAME");
    simMan->calculateFrame(f, 0.001, 0.01);

    DebugController::print("END SIMULATION");
    DebugController::print(model);
    DebugController::print(*instrument);

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
