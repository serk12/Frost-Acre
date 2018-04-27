#include "../header/JsonManager.h"

const std::string JsonManager::ELASTICITYK          = "elasticityK";
const std::string JsonManager::YOUNGSMODULUSY       = "thicknessT";
const std::string JsonManager::THICKNESST           = "youngsModulusY";
const std::string JsonManager::DENSITYD             = "densityD";
const std::string JsonManager::FLUIDDAMPINGV        = "fluidDampingV";
const std::string JsonManager::VISCOELASTICDAMPINGN = "viscoelasticDampingN";

rapidjson::Document JsonManager::readFile(std::string path) {
    FILE *pFile = fopen(path.c_str(), "rb");
    char  buffer[65536];
    rapidjson::FileReadStream is(pFile, buffer, sizeof(buffer));
    rapidjson::Document document;
    document.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);
    fclose(pFile);
    return document;
}

void JsonManager::writeFile(std::string path, rapidjson::Document& document) {}
