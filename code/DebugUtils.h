#ifndef UTILS_HH
#define UTILS_HH

#include <iostream>
#include <string>

#include "SimulatorBundle/header/Instrument.h"
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
        std::cout << "gainOfModeC: "       << std::endl << precalModel.gainOfModeC       << std::endl << std::endl;
        std::cout << "modesOfVibrationZ: " << std::endl << precalModel.modesOfVibrationZ << std::endl << std::endl;
    }

    static void print(const Material& material) {
        std::cout << "elasticityK: "          << material.elasticityK          << std::endl;
        std::cout << "thicknessT: "           << material.thicknessT           << std::endl;
        std::cout << "youngsModulusY: "       << material.youngsModulusY       << std::endl;
        std::cout << "densityD: "             << material.densityD             << std::endl;
        std::cout << "fluidDampingV: "        << material.fluidDampingV        << std::endl;
        std::cout << "viscoelasticDampingN: " << material.viscoelasticDampingN << std::endl << std::endl;
    }

    static void print(const std::vector<Material>& material) {
        for (auto mat : material) {
            Debug::print(mat);
        }
    }

    static void print(const Instrument& instrument) {
        Debug::print(instrument.model3d);
        Debug::print(instrument.precalModel);
    }

    static void print(std::string text) {
        std::cout << text << std::endl;
    }
};

#endif // ifndef UTILS_HH
