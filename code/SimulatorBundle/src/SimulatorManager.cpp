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
        double sum = 0;

        for (int i = 0; i < instrument->precalModel.modesOfVibrationZ.size(); ++i) {
            double num = instrument->precalModel.modesOfVibrationZ(i).real();

            if (!std::isnan(num) and !std::isinf(num)) sum += num;
        }
        note.push_back(sum);
    }

    return note;
}
