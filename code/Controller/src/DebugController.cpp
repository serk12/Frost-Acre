#include "../header/DebugController.h"

std::chrono::high_resolution_clock::time_point DebugController::CLOCK;

void DebugController::print(const Model3D& model3d) {
    std::cout << "vertex: " << std::endl << model3d.vertex << std::endl << std::endl;
    std::cout << "edge: "   << std::endl << model3d.edge   << std::endl << std::endl;
}

void DebugController::print(const PrecalModel& precalModel) {
    std::cout << "massM: "             << std::endl << precalModel.massM             << std::endl << std::endl;
    std::cout << "springK: "           << std::endl << precalModel.springK           << std::endl << std::endl;
    std::cout << "possitiveW: "        << std::endl << precalModel.possitiveW        << std::endl << std::endl;
    std::cout << "negativeW: "         << std::endl << precalModel.negativeW         << std::endl << std::endl;
    std::cout << "gainOfModeC: "       << std::endl << precalModel.gainOfModeC       << std::endl << std::endl;
    std::cout << "modesOfVibrationZ: " << std::endl << precalModel.modesOfVibrationZ << std::endl << std::endl;
}

void DebugController::print(const Material& material) {
    std::cout << "elasticityK: "          << material.elasticityK          << std::endl;
    std::cout << "thicknessT: "           << material.thicknessT           << std::endl;
    std::cout << "youngsModulusY: "       << material.youngsModulusY       << std::endl;
    std::cout << "densityD: "             << material.densityD             << std::endl;
    std::cout << "fluidDampingV: "        << material.fluidDampingV        << std::endl;
    std::cout << "viscoelasticDampingN: " << material.viscoelasticDampingN << std::endl << std::endl;
}

void DebugController::print(const std::vector<Material>& material) {
    for (auto mat : material) {
        DebugController::print(mat);
    }
}

void DebugController::print(const Instrument& instrument) {
    DebugController::print(instrument.model3d);
    DebugController::print(instrument.precalModel);
}

void DebugController::startClock() {
    DebugController::CLOCK = std::chrono::high_resolution_clock::now();
}

void DebugController::print(std::string text) {
    std::chrono::high_resolution_clock::time_point clock2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double> >(clock2 - DebugController::CLOCK);
    std::cerr << text << " in time: " <<  time_span.count() << std::endl;
    DebugController::CLOCK = clock2;
}