#ifndef UTILS_HH
#define UTILS_HH

#include <iostream>
#include <string>
#include "EigenUtils.h"

class Debug {
public:
    static void print(const Model3D& model3d) {
        std::cout << "vertex: " << std::endl << model3d.vertex << std::endl << std::endl;
        std::cout << "edge: "   << std::endl << model3d.edge   << std::endl << std::endl;
    }

    static void print(const PrecalModel& precalModel) {
        std::cout << "massM: "             << std::endl << precalModel.massM             << std::endl << std::endl;
        std::cout << "springK: "           << std::endl << precalModel.springK           << std::endl << std::endl;
        std::cout << "possitiveW: "        << std::endl << precalModel.possitiveW        << std::endl << std::endl;
        std::cout << "negativeW: "         << std::endl << precalModel.negativeW         << std::endl << std::endl;
        std::cout << "modesOfVibrationZ: " << std::endl << precalModel.modesOfVibrationZ << std::endl << std::endl;
        std::cout << "gainOfModeC: "       << std::endl << precalModel.gainOfModeC       << std::endl << std::endl;
    }
};

#endif // ifndef UTILS_HH
