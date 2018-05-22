#include "../header/SimulatorManager.h"

const double SimulatorManager::SampleRate = 200.0;

SimulatorManager::SimulatorManager() : InstrumentSimulator() {}

void SimulatorManager::precallSimulator(Instrument& instrument) {
    this->setInstrument(instrument);
    this->calculatePrecal();
}

void SimulatorManager::calculateFrame(Eigen::VectorXd forcesF, double timeF, double timeV, std::vector<double>& notes) {
    this->calculateImpulsForces(forcesF, timeF);
    int size = timeV * SimulatorManager::SampleRate;
    notes = std::vector<double>(size, 0); int j = 0;
    std::cout << timeV << " " << notes.size() << std::endl;
    if (notes.size() > 1) {
        for (double t = 0; t < timeV; t += 1.0 / SimulatorManager::SampleRate) {
            // std::cout << t << ":t \t";
            this->calculateVibrations(t);

            double sum = 0;
            for (int i = 0; i < instrument->precalModel.modesOfVibrationZ.size(); ++i) {
                double num = instrument->precalModel.modesOfVibrationZ(i).real();
                // std::cout << num << " \t";
                if (!std::isnan(num) and !std::isinf(num)) sum += num;
            }
            // std::cout << sum << ":sum" << std::endl;
            notes[j++] = sum;
        }
    }
}
