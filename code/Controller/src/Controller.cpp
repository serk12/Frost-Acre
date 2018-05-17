#include "../header/Controller.h"

Controller::Controller() {}

Controller::Controller(std::string objFile, std::string jsonFile,
                       std::string midiFile, std::string midiJsonFile) {
    this->objFile      = objFile;
    this->jsonFile     = jsonFile;
    this->midiFile     = midiFile;
    this->midiJsonFile = midiJsonFile;
}

Controller::Controller(std::string midiFile, std::string midiJsonFile) {
    this->midiFile     = midiFile;
    this->midiJsonFile = midiJsonFile;
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

    DebugController::print("INIT PRECAlC");
    simMan->precallSimulator(*instrument);
    DebugController::print("END PRECAlC");

    Eigen::VectorXd f(4 * 3); // #vectors  * #dimensions (3)
    f.fill(0);
    f(0) = 100; f(1)  = 0; f(2)  = 0;

    DebugController::print("INIT FRAME");
    simMan->calculateFrame(f, 0.001, 0.01);
    DebugController::print("END FRAME");

    DebugController::print("END SIMULATION");
    DebugController::print(*instrument);

    delete instrument;
    delete simMan;
}

void Controller::parseMaterial() {
    rapidjson::Document doc = JsonManager::readFile(jsonFile);
    Material material(0);
    this->material.push_back(material);

    for (auto& val : doc[JsonManager::MATERIAL.c_str()].GetArray()) {
        Material material;
        material.thicknessT           = val[JsonManager::THICKNESST.c_str()].GetDouble();
        material.youngsModulusY       = val[JsonManager::YOUNGSMODULUSY.c_str()].GetDouble();
        material.densityD             = val[JsonManager::DENSITYD.c_str()].GetDouble();
        material.fluidDampingV        = val[JsonManager::FLUIDDAMPINGV.c_str()].GetDouble();
        material.viscoelasticDampingN = val[JsonManager::VISCOELASTICDAMPINGN.c_str()].GetDouble();

        this->material.push_back(material);
    }
}



void Controller::writeJsonMidi() {
    std::map<std::string, Eigen::VectorXd> notes = MidiManager::buildMapForces(midiFile);

    rapidjson::Document notesDoc;
    notesDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = notesDoc.GetAllocator();
    rapidjson::Value array(rapidjson::kObjectType);

    for (auto& note : notes) {
        std::stringstream ss;
        ss << note.second;
        array.AddMember(rapidjson::Value().SetString(note.first.c_str(), allocator),
                        rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    }
    notesDoc.AddMember("Map", array, allocator);
    JsonManager::writeFile(midiJsonFile, notesDoc);
}






//
