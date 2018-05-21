#include "../header/JsonManager.h"

const std::string JsonManager::MATERIAL             = "Material";
const std::string JsonManager::YOUNGSMODULUSY       = "youngsModulusY";
const std::string JsonManager::THICKNESST           = "thicknessT";
const std::string JsonManager::DENSITYD             = "densityD";
const std::string JsonManager::FLUIDDAMPINGV        = "fluidDampingV";
const std::string JsonManager::VISCOELASTICDAMPINGN = "viscoelasticDampingN";
const std::string JsonManager::MAPNOTES             = "map";

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
