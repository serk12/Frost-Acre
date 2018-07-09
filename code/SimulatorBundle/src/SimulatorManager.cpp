#include "../header/SimulatorManager.h"

const double SimulatorManager::SampleRate = 44100.0;

SimulatorManager::SimulatorManager() : InstrumentSimulator() {}

void SimulatorManager::precallSimulator(Instrument& instrument) {
    this->setInstrument(instrument);
    this->calculatePrecal();
}

void SimulatorManager::calculateFrame(Eigen::VectorXd forcesF, double timeF, double timeV, std::vector<double>& waves) {
    this->calculateImpulsForces(forcesF, timeF);
    unsigned int size = ceil(timeV * SimulatorManager::SampleRate);
    waves = std::vector<double>(size, 0); double t = 0;

    #pragma omp parallel shared(waves) firstprivate(t, instrument)
    {
        #pragma omp for
        for (unsigned int j = 0; j < size; ++j) {
            t += 1.0 / SimulatorManager::SampleRate;
            Eigen::VectorXd modesOfVibrationZ;
            this->calculateVibrations(t, modesOfVibrationZ);
            waves[j] = 0;
            for (unsigned int i = 0; i < modesOfVibrationZ.size(); i += 3) {
                if (not std::isnan(modesOfVibrationZ[i])     and not std::isinf(modesOfVibrationZ[i]) and
                    not std::isnan(modesOfVibrationZ[i + 1]) and not std::isinf(modesOfVibrationZ[i + 1]) and
                    not std::isnan(modesOfVibrationZ[i + 2]) and not std::isinf(modesOfVibrationZ[i + 2]))
                {
                    double x = this->instrument->model3d.vertex(0, i / 3) + modesOfVibrationZ[i];
                    double y = this->instrument->model3d.vertex(1, i / 3) + modesOfVibrationZ[i + 1];
                    double z = this->instrument->model3d.vertex(2, i / 3) + modesOfVibrationZ[i + 2];
                    waves[j] += this->calculatePickup(x, y, z);
                }
            }
        }
    }
}
