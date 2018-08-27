#ifndef JSONMANAGER_HH
#define JSONMANAGER_HH

#include <iostream>
#include <fstream>

#include "../../../lib/rapidjson/document.h"
#include "../../../lib/rapidjson/filereadstream.h"
#include "../../../lib/rapidjson/stringbuffer.h"
#include "../../../lib/rapidjson/writer.h"

#include "../../Controller/header/DebugController.h"



class JsonManager {
public:
    static const std::string MATERIAL;
    static const std::string YOUNGSMODULUSY;
    static const std::string THICKNESST;
    static const std::string DENSITYD;
    static const std::string FLUIDDAMPINGV;
    static const std::string VISCOELASTICDAMPINGN;

    static const std::string MAPNOTES;

    static const std::string MAGNETICCHARGEDENSITY;
    static const std::string RADIUSPICKUP;
    static const std::string PICKUPPOSSITION;
    static const std::string PICKUP;

    static const std::string RESONANCE;
    static const std::string SCALARFORCELOST;
    static const std::string CONSTANTFORCELOST;
    static const std::string LINEWIDTHRESONANCE;

    static const std::string INSTRUMENT;
    static const std::string RESONANCERATIO;
    static const std::string PRECALMODEL;
    static const std::string MASSM;
    static const std::string SPRINGK;
    static const std::string POSSITIVEW;
    static const std::string NEGATIVEW;
    static const std::string GAINOFMODEC;
    static const std::string VERTEX;
    static const std::string EDGE;
    static const std::string MODEL3D;
    static const std::string EIGENVALUES;
    static const std::string EIGENVECTORS;

    static rapidjson::Document readFile(std::string path);
    static void writeFile(std::string path, rapidjson::Document& document);
};

#endif // ifndef JSONMANAGER_HH
