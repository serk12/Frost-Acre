#include "../header/SimulatorManager.h"

const double SimulatorManager::SampleRate = 44100.0;

SimulatorManager::SimulatorManager() : InstrumentSimulator() {}

void SimulatorManager::precallSimulator(Instrument& instrument) {
    this->setInstrument(instrument);
    this->calculatePrecal();
}

void SimulatorManager::calculateFrame(Eigen::VectorXd forcesF, double timeF, double timeV, std::vector<double>& notes) {
    this->calculateImpulsForces(forcesF, timeF);
    unsigned int size = ceil(timeV * SimulatorManager::SampleRate);
    notes = std::vector<double>(size, 0); double t = 0;

    #pragma omp parallel shared(notes) firstprivate(t, instrument)
    {
        #pragma omp for
        for (unsigned int j = 0; j < size; ++j) {
            t += 1.0 / SimulatorManager::SampleRate;
            notes[j] = this->calculateVibrations(t);
        }
        #pragma omp taskwait
    }
}
