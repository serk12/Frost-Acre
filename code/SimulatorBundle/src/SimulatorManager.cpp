#include "../header/SimulatorManager.h"

SimulatorManager::SimulatorManager() : InstrumentSimulator() {}

void SimulatorManager::precallSimulator(Instrument& instrument) {
    this->setInstrument(instrument);
    this->calculatePrecal();
}

void SimulatorManager::calculateFrame(Eigen::VectorXd forcesF, double timeF, double timeV) {
    this->calculateImpulsForces(forcesF, timeF);
    this->calculateVibrations(timeV);
}
