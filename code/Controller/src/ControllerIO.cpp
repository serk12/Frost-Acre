#include "../header/ControllerIO.h"

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
ControllerIO::ControllerIO(std::string prerenderFile, std::string jsonFile,
                           std::string midiFile, std::string midiJsonFile,
                           std::string wavFile) {
    this->prerenderFile = prerenderFile;
    this->jsonFile      = jsonFile;
    this->midiFile      = midiFile;
    this->midiJsonFile  = midiJsonFile;
    this->wavFile       = wavFile;
}

ControllerIO::ControllerIO(std::string objFile, std::string infoFile, std::string writeFile) {
    this->objFile = objFile;
    if (infoFile[infoFile.size() - 1] == 'd') {
        this->midiFile     = midiFile;
        this->midiJsonFile = midiJsonFile;
    }
    else {
        this->jsonFile      = infoFile;
        this->prerenderFile = writeFile;
    }
}

void ControllerIO::writePrerender(Instrument& instrument) {
    rapidjson::Document prerenderDoc;
    prerenderDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = prerenderDoc.GetAllocator();

    std::stringstream ss;
    rapidjson::Value  instrumentJson(rapidjson::kObjectType);

    // build resonanceRatio json
    ss << instrument.resonanceRatio;
    std::string member = JsonManager::RESONANCERATIO;
    instrumentJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator),
                             rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    ss.str(std::string());
    // build precalModel json
    rapidjson::Value precalModelJson(rapidjson::kObjectType);
    ss << instrument.precalModel.massM;
    member = JsonManager::MASSM;
    precalModelJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator),
                              rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    ss.str(std::string());
    ss << instrument.precalModel.springK;
    member = JsonManager::SPRINGK;
    precalModelJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator),
                              rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    ss.str(std::string());
    ss << instrument.precalModel.possitiveW;
    member = JsonManager::POSSITIVEW;
    precalModelJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator),
                              rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    ss.str(std::string());
    ss << instrument.precalModel.negativeW;
    member = JsonManager::NEGATIVEW;
    precalModelJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator),
                              rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    ss.str(std::string());
    ss << instrument.precalModel.gainOfModeC;
    member = JsonManager::GAINOFMODEC;
    precalModelJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator),
                              rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    ss.str(std::string());
    ss << instrument.precalModel.eigenvalues;
    member = JsonManager::EIGENVALUES;
    precalModelJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator),
                              rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    ss.str(std::string());
    ss << instrument.precalModel.eigenvectors;
    member = JsonManager::EIGENVECTORS;
    precalModelJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator),
                              rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);

    member = JsonManager::PRECALMODEL;
    instrumentJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator), precalModelJson, allocator);

    // build model3d json
    rapidjson::Value model3dJson(rapidjson::kObjectType);
    ss.str(std::string());
    ss << instrument.model3d.vertex;
    member = JsonManager::VERTEX;
    model3dJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator),
                          rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    ss.str(std::string());
    ss << instrument.model3d.edge;
    member = JsonManager::EDGE;
    model3dJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator),
                          rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);
    ss.str(std::string());

    member = JsonManager::MODEL3D;
    instrumentJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator), model3dJson, allocator);

    // build materials
    rapidjson::Value materialsJson(rapidjson::kArrayType);
    for (unsigned int i = 0; i < instrument.material.size(); ++i) {
        rapidjson::Value materialJson(rapidjson::kObjectType);

        member = JsonManager::YOUNGSMODULUSY;
        ss.str(std::string());
        ss << instrument.material[i].youngsModulusY;
        materialJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator),
                               rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);

        member = JsonManager::THICKNESST;
        ss.str(std::string());
        ss << instrument.material[i].thicknessT;
        materialJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator),
                               rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);

        member = JsonManager::DENSITYD;
        ss.str(std::string());
        ss << instrument.material[i].densityD;
        materialJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator),
                               rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);

        member = JsonManager::FLUIDDAMPINGV;
        ss.str(std::string());
        ss << instrument.material[i].fluidDampingV;
        materialJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator),
                               rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);

        member = JsonManager::VISCOELASTICDAMPINGN;
        ss.str(std::string());
        ss << instrument.material[i].viscoelasticDampingN;
        materialJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator),
                               rapidjson::Value().SetString(ss.str().c_str(), allocator), allocator);

        materialsJson.PushBack(materialJson, allocator);
    }

    member = JsonManager::MATERIAL;
    instrumentJson.AddMember(rapidjson::Value().SetString(member.c_str(), allocator), materialsJson, allocator);

    // assemble all
    member = JsonManager::INSTRUMENT;
    prerenderDoc.AddMember(rapidjson::Value().SetString(member.c_str(), allocator), instrumentJson, allocator);

    JsonManager::writeFile(prerenderFile, prerenderDoc);
}

void ControllerIO::writeJsonMidi(bool def) {
    std::map<std::string, Eigen::VectorXd> notes = MidiManager::buildMapForces(midiFile);

    rapidjson::Document notesDoc;
    notesDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = notesDoc.GetAllocator();
    rapidjson::Value map(rapidjson::kObjectType);

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
        map.AddMember(rapidjson::Value().SetString(note.first.c_str(), allocator),
                      rapidjson::Value().SetString(ss.str().c_str(),   allocator), allocator);
        ss.str(std::string());
    }
    std::string member = JsonManager::MAPNOTES;
    notesDoc.AddMember(rapidjson::Value().SetString(member.c_str(), allocator), map, allocator);
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
    // read materlial

    for (auto& val : doc[JsonManager::INSTRUMENT.c_str()][JsonManager::MATERIAL.c_str()].GetArray())
    {
        Material material;
        material.thicknessT           = std::stod(val[JsonManager::THICKNESST.c_str()].GetString());
        material.youngsModulusY       = std::stod(val[JsonManager::YOUNGSMODULUSY.c_str()].GetString());
        material.densityD             = std::stod(val[JsonManager::DENSITYD.c_str()].GetString());
        material.fluidDampingV        = std::stod(val[JsonManager::FLUIDDAMPINGV.c_str()].GetString());
        material.viscoelasticDampingN = std::stod(val[JsonManager::VISCOELASTICDAMPINGN.c_str()].GetString());

        instrument.material.push_back(material);
    }
    return instrument;
}

void ControllerIO::readJson(Pickup& pickup, std::vector<Material>& materials, Resonance& resonance) {
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

    pickup.radiusPickup          = doc[JsonManager::PICKUP.c_str()][JsonManager::RADIUSPICKUP.c_str()].GetDouble();
    pickup.pickupPossitionX      = doc[JsonManager::PICKUP.c_str()][JsonManager::PICKUPPOSSITION.c_str()][0].GetDouble();
    pickup.pickupPossitionY      = doc[JsonManager::PICKUP.c_str()][JsonManager::PICKUPPOSSITION.c_str()][1].GetDouble();
    pickup.pickupPossitionZ      = doc[JsonManager::PICKUP.c_str()][JsonManager::PICKUPPOSSITION.c_str()][2].GetDouble();
    pickup.magneticChargeDensity = doc[JsonManager::PICKUP.c_str()][JsonManager::MAGNETICCHARGEDENSITY.c_str()].GetDouble();

    resonance.scalarForceLost   = doc[JsonManager::RESONANCE.c_str()][JsonManager::SCALARFORCELOST.c_str()].GetDouble();
    resonance.constantForceLost = doc[JsonManager::RESONANCE.c_str()][JsonManager::CONSTANTFORCELOST.c_str()].GetDouble();
}



std::map<int, Eigen::VectorXd> ControllerIO::getMapForces() {
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

std::vector<Pluck> ControllerIO::parseMidiFile() {
    return MidiManager::parseMidiFile(midiFile);
}

void ControllerIO::writeWav(std::vector<double> sound, int sampleRate) {
    WavManager::writeWav(wavFile, sound, sampleRate);
}
