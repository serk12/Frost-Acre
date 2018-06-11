#include "../header/Controller.h"

Controller::Controller() {}

Controller::Controller(std::string objFile, std::string jsonFile,
                       std::string midiFile, std::string midiJsonFile,
                       std::string wavFile) {
    this->objFile      = objFile;
    this->jsonFile     = jsonFile;
    this->midiFile     = midiFile;
    this->midiJsonFile = midiJsonFile;
    this->wavFile      = wavFile;
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
    this->readJson();
    DebugController::print("END PARSE");

    SimulatorManager simMan = SimulatorManager();
    Instrument instrument   = Instrument(material, model);

    DebugController::print("INIT PRECALC");
    simMan.precallSimulator(instrument);
    DebugController::print("END PRECALC");

    std::vector<Pluck> plucks = MidiManager::parseMidiFile(midiFile);
    this->getMapForces(midiJsonFile);

    float max = 0;
    for (auto& pluck : plucks) {
        int endNote = pluck.timeDur + pluck.timeStart;
        if (endNote > max) max = endNote;
    }
    std::vector<double> sound(ceil(max * SimulatorManager::SampleRate), 0);

    for (auto& pluck : plucks) {
        DebugController::print("INIT FRAME");
        DebugController::print(pluck);
        std::vector<double> notes;
        simMan.calculateFrame(this->notes[pluck.note], pluck.timeForce, pluck.timeDur, notes);
        int j = ceil(pluck.timeStart * SimulatorManager::SampleRate);
        for (unsigned int i = 0; i < notes.size(); ++i) {
            sound[j + i] += notes[i];
            // std::cout << sound[j + i] << std::endl;
        }
        DebugController::print("END FRAME"); break;
    }

    DebugController::print("WRITING WAV");
    WavManager::writeWav(wavFile, sound, (int)(SimulatorManager::SampleRate));
    DebugController::print("END SIMULATION");
    DebugController::print(instrument);
}

void Controller::readJson() {
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

void Controller::writeJsonMidi(bool def) {
    std::map<std::string, Eigen::VectorXd> notes = MidiManager::buildMapForces(midiFile);

    rapidjson::Document notesDoc;
    notesDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = notesDoc.GetAllocator();
    rapidjson::Value array(rapidjson::kObjectType);

    int size = 4 * 3; // #vectors  * #dimensions (3)
    Eigen::VectorXd f(size);
    if (def) {
        f.fill(0);
        f(0) = 1;
        f(1) = 1;
        f(2) = 1;
        // for (double i = 0 * 3; i < size; ++i) {
        //     f(i) = (1.0 / sqrt(2 * 3.1415)) * pow(std::exp(1.0), -((i / (96.0 * 3.0 - size * 3.0)) * (i / (96.0 * 3.0 - size * 3.0)) / 2.0));
        // }
    }
    else {
        std::cin >> size;
        Eigen::VectorXd f(size);
    }

    for (auto& note : notes) {
        if (!def) {
            double point;
            for (int i = 0; i < size; ++i) {
                std::cin >> point;
                f(i) = point;
            }
        }
        std::stringstream ss;
        ss << f;
        array.AddMember(rapidjson::Value().SetString(note.first.c_str(), allocator),
                        rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    }
    std::string member = JsonManager::MAPNOTES;
    notesDoc.AddMember(rapidjson::Value().SetString(member.c_str(), allocator), array, allocator);
    JsonManager::writeFile(midiJsonFile, notesDoc);
}

std::vector<double> explode(const std::string& s, const char delim)
{
    std::vector<double> result;
    std::istringstream  iss(s);
    for (std::string token; std::getline(iss, token, delim);)
    {
        result.push_back(std::stod(std::move(token)));
    }
    return result;
}

std::map<int, Eigen::VectorXd> Controller::getMapForces(std::string jsonFile) {
    rapidjson::Document doc = JsonManager::readFile(jsonFile);
    for (auto& val : doc[JsonManager::MAPNOTES.c_str()].GetObject()) {
        std::vector<double> forces = explode(val.value.GetString(), '\n');
        Eigen::VectorXd     f      = Eigen::VectorXd::Map(forces.data(), forces.size());
        this->notes[std::stoi(val.name.GetString())] = f;
    }

    return notes;
}


//
