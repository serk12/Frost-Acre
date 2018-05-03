#include "../header/SimulatorManager.h"

SimulatorManager::SimulatorManager() : InstrumentSimulator() {}

void SimulatorManager::precallSimulator(Instrument& instrument) {
    this->setInstrument(instrument);
    this->calculatePrecal();
}

void SimulatorManager::calculateFrame(Eigen::VectorXd forcesF, double timeF, double timeV) {
    DebugController::print("NANI");
    this->calculateImpulsForces(forcesF, timeF);
    DebugController::print("NANI2");
    this->calculateVibrations(timeV);
    DebugController::print("NANI3");
}
