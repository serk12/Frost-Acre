#include "../header/SimulatorManager.h"

const double SimulatorManager::SampleRate =  1.0 / 44100.0;

SimulatorManager::SimulatorManager() : InstrumentSimulator() {}

void SimulatorManager::precallSimulator(Instrument& instrument) {
    this->setInstrument(instrument);
    this->calculatePrecal();
}

void SimulatorManager::calculateFrame(Eigen::VectorXd forcesF, double timeF, double timeV) {
    this->calculateImpulsForces(forcesF, timeF);

    for (double t = 0; t < timeV; t +=  SimulatorManager::SampleRate) {
        this->calculateVibrations(t);
    }
}
