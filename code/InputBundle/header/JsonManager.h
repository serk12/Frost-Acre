#ifndef JSONREADER_HH
#define JSONREADER_HH

#include "../../../lib/rapidjson/document.h"
#include "../../../lib/rapidjson/filereadstream.h"

#include "../../DebugUtils.h"

class JsonManager {
public:
    static const std::string ELASTICITYK;
    static const std::string YOUNGSMODULUSY;
    static const std::string THICKNESST;
    static const std::string DENSITYD;
    static const std::string FLUIDDAMPINGV;
    static const std::string VISCOELASTICDAMPINGN;

    static rapidjson::Document readFile(std::string path);
    static void writeFile(std::string path, rapidjson::Document& document);
};

#endif // ifndef JSONREADER_HH
