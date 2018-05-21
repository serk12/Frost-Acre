#include "../header/SimulatorManager.h"

const double SimulatorManager::SampleRate =  1.0 / 44000.0;

SimulatorManager::SimulatorManager() : InstrumentSimulator() {}

void SimulatorManager::precallSimulator(Instrument& instrument) {
    this->setInstrument(instrument);
    this->calculatePrecal();
}

std::list<double> SimulatorManager::calculateFrame(Eigen::VectorXd forcesF, double timeF, double timeV) {
    this->calculateImpulsForces(forcesF, timeF);
    std::list<double> note;

    for (double t = 0; t < timeV; t +=  SimulatorManager::SampleRate) {
        this->calculateVibrations(t);
        note.push_back(instrument->precalModel.modesOfVibrationZ.real().sum());
    }

    return note;
}
