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
    for (unsigned int j = 0; j < size; ++j) {
        t += 1.0 / SimulatorManager::SampleRate;
        this->calculateVibrations(t);

        double sum = 0;
        for (int i = 0; i < instrument->precalModel.modesOfVibrationZ.size(); ++i) {
            double num = instrument->precalModel.modesOfVibrationZ(i).real();
            if (!std::isnan(num) and !std::isinf(num)) {
                sum += num;
                // std::cout << num << " ";
            }
        }
        // std::cout << std::endl << sum << std::endl;
        notes[j] = sum;
    }
}
