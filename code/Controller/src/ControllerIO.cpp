#include "../header/ControllerIO.h"

const int ControllerIO::textSize    = 32;
const int ControllerIO::deltaXMidi  = 1;
const int ControllerIO::initMidiTex = 40;  // 40: E2
const int ControllerIO::initMidi    = 13;  // 19: D0
const int ControllerIO::endMidi     = 120; // 120: B8?

template<class T>
void explode(const std::string& s, const char delim, std::vector<T>& result)
{
    std::istringstream iss(s);
    for (std::string token; std::getline(iss, token, delim);)
    {
        std::istringstream is(std::move(token));
        if (std::move(token) != "") {
            T aux; is >> aux;
            result.push_back(aux);
        }
    }
}

template<class T>
void explode(const std::string& s, const char delim, const char delim2, std::vector<std::vector<T> >& result)
{
    std::istringstream iss(s);
    for (std::string token; std::getline(iss, token, delim);)
    {
        std::vector<T> aux;
        explode(std::move(token), delim2, aux);
        result.push_back(aux);
    }
}

ControllerIO::ControllerIO() {}
ControllerIO::ControllerIO(std::string prerenderFile, std::string midiFile,
                           std::string midiJsonFile, std::string wavFile) {
    this->prerenderFile = prerenderFile;
    this->midiFile      = midiFile;
    this->midiJsonFile  = midiJsonFile;
    this->wavFile       = wavFile;
}

ControllerIO::ControllerIO(std::string objFile, std::string jsonFile, std::string prerenderFile) {
    this->objFile       = objFile;
    this->jsonFile      = jsonFile;
    this->prerenderFile = prerenderFile;
}

ControllerIO::ControllerIO(std::string objFile, std::string midiJsonFile) {
    this->objFile      = objFile;
    this->midiJsonFile = midiJsonFile;
}

void ControllerIO::writePrerender(Instrument& instrument) {
    rapidjson::Document prerenderDoc;
    prerenderDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = prerenderDoc.GetAllocator();

    std::stringstream ss;
    rapidjson::Value  instrumentJson(rapidjson::kObjectType);

    // build resonanceRatio json
    ss << instrument.resonanceRatio;
    instrumentJson.AddMember(rapidjson::Value().SetString(JsonManager::RESONANCERATIO.c_str(), allocator),
                             rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    ss.str(std::string());
    // build precalModel json
    rapidjson::Value precalModelJson(rapidjson::kObjectType);
    ss << instrument.precalModel.massM;
    precalModelJson.AddMember(rapidjson::Value().SetString(JsonManager::MASSM.c_str(), allocator),
                              rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    ss.str(std::string());
    ss << instrument.precalModel.springK;
    precalModelJson.AddMember(rapidjson::Value().SetString(JsonManager::SPRINGK.c_str(), allocator),
                              rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    ss.str(std::string());
    ss << instrument.precalModel.possitiveW;
    precalModelJson.AddMember(rapidjson::Value().SetString(JsonManager::POSSITIVEW.c_str(), allocator),
                              rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    ss.str(std::string());
    ss << instrument.precalModel.negativeW;
    precalModelJson.AddMember(rapidjson::Value().SetString(JsonManager::NEGATIVEW.c_str(), allocator),
                              rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    ss.str(std::string());
    ss << instrument.precalModel.gainOfModeC;
    precalModelJson.AddMember(rapidjson::Value().SetString(JsonManager::GAINOFMODEC.c_str(), allocator),
                              rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    ss.str(std::string());
    ss << instrument.precalModel.eigenvalues;
    precalModelJson.AddMember(rapidjson::Value().SetString(JsonManager::EIGENVALUES.c_str(), allocator),
                              rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    ss.str(std::string());
    ss << instrument.precalModel.eigenvectors;
    precalModelJson.AddMember(rapidjson::Value().SetString(JsonManager::EIGENVECTORS.c_str(), allocator),
                              rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);

    instrumentJson.AddMember(rapidjson::Value().SetString(JsonManager::PRECALMODEL.c_str(), allocator), precalModelJson, allocator);

    // build model3d json
    rapidjson::Value model3dJson(rapidjson::kObjectType);

    ss.str(std::string());
    ss << instrument.model3d.vertex;
    model3dJson.AddMember(rapidjson::Value().SetString(JsonManager::VERTEX.c_str(), allocator),
                          rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    ss.str(std::string());
    ss << instrument.model3d.edge;
    model3dJson.AddMember(rapidjson::Value().SetString(JsonManager::EDGE.c_str(), allocator),
                          rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);

    instrumentJson.AddMember(rapidjson::Value().SetString(JsonManager::MODEL3D.c_str(), allocator), model3dJson, allocator);

    // assemble all instrument
    prerenderDoc.AddMember(rapidjson::Value().SetString(JsonManager::INSTRUMENT.c_str(), allocator), instrumentJson, allocator);

    // build materials
    rapidjson::Value materialsJson(rapidjson::kArrayType);
    for (unsigned int i = 1; i < instrument.material.size(); ++i) {
        rapidjson::Value materialJson(rapidjson::kObjectType);
        materialJson.AddMember(rapidjson::Value().SetString(JsonManager::YOUNGSMODULUSY.c_str(), allocator),
                               rapidjson::Value().SetDouble(instrument.material[i].youngsModulusY), allocator);
        materialJson.AddMember(rapidjson::Value().SetString(JsonManager::THICKNESST.c_str(), allocator),
                               rapidjson::Value().SetDouble(instrument.material[i].thicknessT), allocator);
        materialJson.AddMember(rapidjson::Value().SetString(JsonManager::DENSITYD.c_str(), allocator),
                               rapidjson::Value().SetDouble(instrument.material[i].densityD), allocator);
        materialJson.AddMember(rapidjson::Value().SetString(JsonManager::FLUIDDAMPINGV.c_str(), allocator),
                               rapidjson::Value().SetDouble(instrument.material[i].fluidDampingV), allocator);
        materialJson.AddMember(rapidjson::Value().SetString(JsonManager::VISCOELASTICDAMPINGN.c_str(), allocator),
                               rapidjson::Value().SetDouble(instrument.material[i].viscoelasticDampingN), allocator);
        materialsJson.PushBack(materialJson, allocator);
    }
    prerenderDoc.AddMember(rapidjson::Value().SetString(JsonManager::MATERIAL.c_str(), allocator), materialsJson, allocator);

    // build pickup
    rapidjson::Value pickupJson(rapidjson::kObjectType);

    rapidjson::Value pickupPosJson(rapidjson::kArrayType);
    pickupPosJson.PushBack(rapidjson::Value().SetDouble(instrument.pickup.pickupPossitionX), allocator);
    pickupPosJson.PushBack(rapidjson::Value().SetDouble(instrument.pickup.pickupPossitionY), allocator);
    pickupPosJson.PushBack(rapidjson::Value().SetDouble(instrument.pickup.pickupPossitionZ), allocator);
    pickupJson.AddMember(rapidjson::Value().SetString(JsonManager::PICKUPPOSSITION.c_str(), allocator), pickupPosJson, allocator);

    pickupJson.AddMember(rapidjson::Value().SetString(JsonManager::MAGNETICCHARGEDENSITY.c_str(), allocator),
                         rapidjson::Value().SetDouble(instrument.pickup.magneticChargeDensity), allocator);
    pickupJson.AddMember(rapidjson::Value().SetString(JsonManager::RADIUSPICKUP.c_str(), allocator),
                         rapidjson::Value().SetDouble(instrument.pickup.radiusPickup), allocator);

    prerenderDoc.AddMember(rapidjson::Value().SetString(JsonManager::PICKUP.c_str(), allocator), pickupJson, allocator);

    rapidjson::Value resonanceJson(rapidjson::kObjectType);

    // build resonance
    resonanceJson.AddMember(rapidjson::Value().SetString(JsonManager::SCALARFORCELOST.c_str(), allocator),
                            rapidjson::Value().SetDouble(instrument.resonance.scalarForceLost), allocator);
    resonanceJson.AddMember(rapidjson::Value().SetString(JsonManager::CONSTANTFORCELOST.c_str(), allocator),
                            rapidjson::Value().SetDouble(instrument.resonance.constantForceLost), allocator);

    prerenderDoc.AddMember(rapidjson::Value().SetString(JsonManager::RESONANCE.c_str(), allocator), resonanceJson, allocator);

    JsonManager::writeFile(prerenderFile, prerenderDoc);
}

void ControllerIO::writeJsonMidi() {
    Model3D model         = ObjManager::readObj(objFile);
    TextureVector texture = ObjManager::readTexture(objFile);

    rapidjson::Document notesDoc;
    notesDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = notesDoc.GetAllocator();
    rapidjson::Value map(rapidjson::kObjectType);

    int size = model.vertex.size();
    std::map<std::string, Eigen::VectorXd> notes;
    Eigen::VectorXd f(size);
    for (int i = ControllerIO::initMidi; i < ControllerIO::endMidi; ++i) {
        notes[std::to_string(i)] = f;
    }

    for (unsigned int i = 0; i < texture.size(); ++i) {
        int note = (floor(texture[i].second * ControllerIO::textSize) * ControllerIO::deltaXMidi) +
                   floor(texture[i].first * ControllerIO::textSize) +
                   ControllerIO::initMidiTex;

        if (note < ControllerIO::endMidi) {
            notes[std::to_string(note)](i * 3)       = 1;
            notes[std::to_string(note)]((i * 3) + 1) = 1;
            notes[std::to_string(note)]((i * 3) + 2) = 1;
        }
    }

    for (int i = ControllerIO::initMidi; i < ControllerIO::endMidi; ++i) {
        std::stringstream ss;
        ss << notes[std::to_string(i)];
        map.AddMember(rapidjson::Value().SetString(std::to_string(i).c_str(), allocator),
                      rapidjson::Value().SetString(ss.str().c_str(),   allocator), allocator);
        ss.str(std::string());
    }

    notesDoc.AddMember(rapidjson::Value().SetString(JsonManager::MAPNOTES.c_str(), allocator), map, allocator);
    JsonManager::writeFile(midiJsonFile, notesDoc);
}

Instrument ControllerIO::readPrerender() {
    Instrument instrument;
    rapidjson::Document doc = JsonManager::readFile(prerenderFile);
    // read obj
    std::vector<std::vector<int> > auxI;
    explode(doc[JsonManager::INSTRUMENT.c_str()][JsonManager::MODEL3D.c_str()][JsonManager::EDGE.c_str()].GetString(), '\n', ' ', auxI);
    instrument.model3d.edge = Eigen::MatrixXi::Zero(auxI.size(), auxI[0].size());
    for (unsigned int i = 0; i < auxI.size(); ++i) instrument.model3d.edge.row(i) = Eigen::VectorXi::Map(auxI[i].data(), auxI[i].size());

    std::vector<std::vector<double> > aux;
    explode(doc[JsonManager::INSTRUMENT.c_str()][JsonManager::MODEL3D.c_str()][JsonManager::VERTEX.c_str()].GetString(), '\n', ' ', aux);
    instrument.model3d.vertex = Eigen::Matrix3Xd::Zero(aux.size(), aux[0].size());
    for (unsigned int i = 0; i < aux.size(); ++i) instrument.model3d.vertex.row(i) = Eigen::VectorXd::Map(aux[i].data(), aux[i].size());

    // read precalModel
    aux.clear();
    explode(doc[JsonManager::INSTRUMENT.c_str()][JsonManager::PRECALMODEL.c_str()][JsonManager::SPRINGK.c_str()].GetString(), '\n', ' ', aux);
    instrument.precalModel.springK = Eigen::MatrixXd::Zero(aux.size(), aux[0].size());
    for (unsigned int i = 0; i < aux.size(); ++i) instrument.precalModel.springK.row(i) = Eigen::VectorXd::Map(aux[i].data(), aux[i].size());

    std::vector<std::vector<std::complex<double> > > auxMC;
    explode(doc[JsonManager::INSTRUMENT.c_str()][JsonManager::PRECALMODEL.c_str()][JsonManager::EIGENVALUES.c_str()].GetString(), '\n', ' ', auxMC);
    instrument.precalModel.eigenvalues = Eigen::MatrixXd::Zero(auxMC.size(), auxMC[0].size());
    for (unsigned int i = 0; i < auxMC.size(); ++i) instrument.precalModel.eigenvalues.row(i) = Eigen::VectorXcd::Map(auxMC[i].data(), auxMC[i].size());

    auxMC.clear();
    explode(doc[JsonManager::INSTRUMENT.c_str()][JsonManager::PRECALMODEL.c_str()][JsonManager::EIGENVECTORS.c_str()].GetString(), '\n', ' ', auxMC);
    instrument.precalModel.eigenvectors = Eigen::MatrixXd::Zero(auxMC.size(), auxMC[0].size());
    for (unsigned int i = 0; i < auxMC.size(); ++i) instrument.precalModel.eigenvectors.row(i) = Eigen::VectorXcd::Map(auxMC[i].data(), auxMC[i].size());

    std::vector<std::complex<double> > auxC;
    explode(doc[JsonManager::INSTRUMENT.c_str()][JsonManager::PRECALMODEL.c_str()][JsonManager::POSSITIVEW.c_str()].GetString(), '\n', auxC);
    instrument.precalModel.possitiveW = Eigen::VectorXcd::Map(auxC.data(), auxC.size());

    auxC.clear();
    explode(doc[JsonManager::INSTRUMENT.c_str()][JsonManager::PRECALMODEL.c_str()][JsonManager::NEGATIVEW.c_str()].GetString(), '\n', auxC);
    instrument.precalModel.negativeW = Eigen::VectorXcd::Map(auxC.data(), auxC.size());

    auxC.clear();
    explode(doc[JsonManager::INSTRUMENT.c_str()][JsonManager::PRECALMODEL.c_str()][JsonManager::GAINOFMODEC.c_str()].GetString(), '\n', auxC);
    instrument.precalModel.gainOfModeC = Eigen::VectorXcd::Map(auxC.data(), auxC.size());

    std::vector<double> auxD;
    explode(doc[JsonManager::INSTRUMENT.c_str()][JsonManager::PRECALMODEL.c_str()][JsonManager::MASSM.c_str()].GetString(), '\n', auxD);
    instrument.precalModel.massM = Eigen::VectorXd::Map(auxD.data(), auxD.size());

    // read resonanceRatio
    auxD.clear();
    explode(doc[JsonManager::INSTRUMENT.c_str()][JsonManager::RESONANCERATIO.c_str()].GetString(), '\n', auxD);
    instrument.resonanceRatio = Eigen::VectorXd::Map(auxD.data(), auxD.size());

    // read jsonFile
    this->readJson(instrument.pickup, instrument.material, instrument.resonance, doc);

    return instrument;
}

void ControllerIO::readJson(Pickup& pickup, std::vector<Material>& materials, Resonance& resonance, rapidjson::Document& doc) {
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

    pickup.radiusPickup          = doc[JsonManager::PICKUP.c_str()][JsonManager::RADIUSPICKUP.c_str()].GetDouble();
    pickup.pickupPossitionX      = doc[JsonManager::PICKUP.c_str()][JsonManager::PICKUPPOSSITION.c_str()][0].GetDouble();
    pickup.pickupPossitionY      = doc[JsonManager::PICKUP.c_str()][JsonManager::PICKUPPOSSITION.c_str()][1].GetDouble();
    pickup.pickupPossitionZ      = doc[JsonManager::PICKUP.c_str()][JsonManager::PICKUPPOSSITION.c_str()][2].GetDouble();
    pickup.magneticChargeDensity = doc[JsonManager::PICKUP.c_str()][JsonManager::MAGNETICCHARGEDENSITY.c_str()].GetDouble();

    resonance.scalarForceLost   = doc[JsonManager::RESONANCE.c_str()][JsonManager::SCALARFORCELOST.c_str()].GetDouble();
    resonance.constantForceLost = doc[JsonManager::RESONANCE.c_str()][JsonManager::CONSTANTFORCELOST.c_str()].GetDouble();
}

void ControllerIO::readJson(Pickup& pickup, std::vector<Material>& materials, Resonance& resonance) {
    rapidjson::Document doc = JsonManager::readFile(jsonFile);
    ControllerIO::readJson(pickup, materials, resonance, doc);
}

std::map<int, Eigen::VectorXd> ControllerIO::readJsonMidi() {
    std::map<int, Eigen::VectorXd> notes;
    rapidjson::Document doc = JsonManager::readFile(midiJsonFile);
    for (auto& val : doc[JsonManager::MAPNOTES.c_str()].GetObject()) {
        std::vector<double> forces;
        explode(val.value.GetString(), '\n', forces);
        Eigen::VectorXd f = Eigen::VectorXd::Map(forces.data(), forces.size());
        notes[std::stoi(val.name.GetString())] = f;
    }

    return notes;
}

Model3D ControllerIO::readObj() {
    return ObjManager::readObj(objFile);
}

std::vector<Pluck> ControllerIO::readMidiFile() {
    return MidiManager::readMidiFile(midiFile);
}

void ControllerIO::writeWav(std::vector<double> sound, int sampleRate) {
    WavManager::writeWav(wavFile, sound, sampleRate);
}
