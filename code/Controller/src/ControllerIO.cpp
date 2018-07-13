#include "../header/ControllerIO.h"

ControllerIO::ControllerIO() {}
ControllerIO::ControllerIO(std::string objFile, std::string jsonFile,
                           std::string midiFile, std::string midiJsonFile,
                           std::string wavFile) {
    this->objFile      = objFile;
    this->jsonFile     = jsonFile;
    this->midiFile     = midiFile;
    this->midiJsonFile = midiJsonFile;
    this->wavFile      = wavFile;
}

ControllerIO::ControllerIO(std::string objFile, std::string midiFile, std::string midiJsonFile) {
    this->objFile      = objFile;
    this->midiFile     = midiFile;
    this->midiJsonFile = midiJsonFile;
}


void ControllerIO::writeJsonMidi(bool def) {
    std::map<std::string, Eigen::VectorXd> notes = MidiManager::buildMapForces(midiFile);

    rapidjson::Document notesDoc;
    notesDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = notesDoc.GetAllocator();
    rapidjson::Value array(rapidjson::kObjectType);

    Model3D model = ObjManager::readObj(objFile);
    int     size  = model.vertex.size();
    Eigen::VectorXd f(size);
    if (def) {
        f.fill(0);
        f(0) = 1;
        f(1) = 1;
        f(2) = 1;
        // for (double i = 0 * 3; i < size; ++i) {
        //     f(i) = (1.0 / sqrt(2 * 3.1415)) * pow(std::exp(1.0), -((i / (96.0
        // * 3.0 - size * 3.0)) * (i / (96.0 * 3.0 - size * 3.0)) / 2.0));
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

void ControllerIO::readJson(Pickup& pickup, std::vector<Material>& materials) {
    rapidjson::Document doc = JsonManager::readFile(jsonFile);

    Material material(0);
    materials.push_back(material);
    for (auto& val : doc[JsonManager::MATERIAL.c_str()].GetArray()) {
        Material material;
        material.thicknessT           = val[JsonManager::THICKNESST.c_str()].GetDouble();
        material.youngsModulusY       = val[JsonManager::YOUNGSMODULUSY.c_str()].GetDouble();
        material.densityD             = val[JsonManager::DENSITYD.c_str()].GetDouble();
        material.fluidDampingV        = val[JsonManager::FLUIDDAMPINGV.c_str()].GetDouble();
        material.viscoelasticDampingN = val[JsonManager::VISCOELASTICDAMPINGN.c_str()].GetDouble();

        materials.push_back(material);
    }
    // for (auto& val : doc[JsonManager::PICKUP.c_str()].GetObject()) {
    //     std::cout << val.name.GetDouble
    // }

    pickup.radiusPickup          = doc[JsonManager::PICKUP.c_str()][JsonManager::RADIUSPICKUP.c_str()].GetDouble();
    pickup.pickupPossitionX      = doc[JsonManager::PICKUP.c_str()][JsonManager::PICKUPPOSSITION.c_str()][0].GetDouble();
    pickup.pickupPossitionY      = doc[JsonManager::PICKUP.c_str()][JsonManager::PICKUPPOSSITION.c_str()][1].GetDouble();
    pickup.pickupPossitionZ      = doc[JsonManager::PICKUP.c_str()][JsonManager::PICKUPPOSSITION.c_str()][2].GetDouble();
    pickup.magneticChargeDensity = doc[JsonManager::PICKUP.c_str()][JsonManager::MAGNETICCHARGEDENSITY.c_str()].GetDouble();
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

std::map<int, Eigen::VectorXd> ControllerIO::getMapForces() {
    std::map<int, Eigen::VectorXd> notes;
    rapidjson::Document doc = JsonManager::readFile(midiJsonFile);
    for (auto& val : doc[JsonManager::MAPNOTES.c_str()].GetObject()) {
        std::vector<double> forces = explode(val.value.GetString(), '\n');
        Eigen::VectorXd     f      = Eigen::VectorXd::Map(forces.data(), forces.size());
        notes[std::stoi(val.name.GetString())] = f;
    }

    return notes;
}

Model3D ControllerIO::readObj() {
    return ObjManager::readObj(objFile);
}

std::vector<Pluck> ControllerIO::parseMidiFile() {
    return MidiManager::parseMidiFile(midiFile);
}

void ControllerIO::writeWav(std::vector<double> sound, int sampleRate) {
    WavManager::writeWav(wavFile, sound, sampleRate);
}
