#include "../header/JsonManager.h"

const std::string JsonManager::MATERIAL              = "Material";
const std::string JsonManager::YOUNGSMODULUSY        = "youngsModulusY";
const std::string JsonManager::THICKNESST            = "thicknessT";
const std::string JsonManager::DENSITYD              = "densityD";
const std::string JsonManager::FLUIDDAMPINGV         = "fluidDampingV";
const std::string JsonManager::VISCOELASTICDAMPINGN  = "viscoelasticDampingN";
const std::string JsonManager::MAPNOTES              = "map";
const std::string JsonManager::MAGNETICCHARGEDENSITY = "MagneticChargeDensity";
const std::string JsonManager::RADIUSPICKUP          = "radiusPickup";
const std::string JsonManager::PICKUPPOSSITION       = "pickupPossition";
const std::string JsonManager::PICKUP                = "Pickup";
const std::string JsonManager::RESONANCE             = "Resonance";
const std::string JsonManager::SCALARFORCELOST       = "scalarForceLost";
const std::string JsonManager::CONSTANTFORCELOST     = "constantForceLost";
const std::string JsonManager::INSTRUMENT            = "instrument";
const std::string JsonManager::RESONANCERATIO        = "resonanceRatio";
const std::string JsonManager::PRECALMODEL           = "precalModel";
const std::string JsonManager::MASSM                 = "massM";
const std::string JsonManager::SPRINGK               = "springK";
const std::string JsonManager::POSSITIVEW            = "possitiveW";
const std::string JsonManager::NEGATIVEW             = "negativeW";
const std::string JsonManager::GAINOFMODEC           = "gainofmodeC";
const std::string JsonManager::VERTEX                = "vertex";
const std::string JsonManager::EDGE                  = "edge";
const std::string JsonManager::MODEL3D               = "model3d";
const std::string JsonManager::EIGENVALUES           = "eigenvalues";
const std::string JsonManager::EIGENVECTORS          = "eigenvectors";
const std::string JsonManager::LINEWIDTHRESONANCE    = "linewidthResonance";

rapidjson::Document JsonManager::readFile(std::string path) {
    FILE *file = fopen(path.c_str(), "rb");
    char  buffer[65536];
    rapidjson::FileReadStream is(file, buffer, sizeof(buffer));
    rapidjson::Document document;
    document.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);
    fclose(file);
    return document;
}

void JsonManager::writeFile(std::string path, rapidjson::Document& document) {
    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

    std::ofstream file;
    file.open(path);
    file << strbuf.GetString();
    file.close();
}
