#include "../header/SimulatorManager.h"

const double SimulatorManager::SampleRate = 44100.0;

SimulatorManager::SimulatorManager() : InstrumentSimulator() {}

void SimulatorManager::precallSimulator(Instrument& instrument) {
    this->setInstrument(instrument);
    this->calculatePrecal();
}

void SimulatorManager::calculateFrame(Eigen::VectorXd forcesF, double timeF, double timeV, std::vector<double>& notes) {
    this->calculateImpulsForces(forcesF, timeF);
    notes = std::vector<double>(timeV * SimulatorManager::SampleRate + 1, 0); int j = 0;

    for (double t = 0; t < timeV; t += 1.0 / SimulatorManager::SampleRate) {
        this->calculateVibrations(t);

        double sum = 0;
        for (int i = 0; i < instrument->precalModel.modesOfVibrationZ.size(); ++i) {
            double num = instrument->precalModel.modesOfVibrationZ(i).real();

            if (!std::isnan(num) and !std::isinf(num)) sum += num;
        }
        notes[j++] = sum;
    }
<<<<<<< HEAD
=======
    std::cout << j << " " << notes.size() << std::endl;
>>>>>>> 674a76285404283281174596964b3c97aea857e3
}
