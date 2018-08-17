#include "../header/SimulatorManager.h"

const double SimulatorManager::SampleRate = 44100.0;
const bool   SimulatorManager::pickup     = false;
const bool   SimulatorManager::resonance  = true;

SimulatorManager::SimulatorManager() : InstrumentSimulator() {}

void SimulatorManager::setPrerender(Instrument& instrument) {
    this->setInstrument(instrument);
    resonanceForce = Eigen::VectorXd::Zero(instrument.precalModel.possitiveW.size());

    this->setRadiusPickup(instrument.pickup.radiusPickup);
    this->setMagneticChargeDensity(instrument.pickup.magneticChargeDensity);
    this->setPickupPossition(instrument.pickup.pickupPossitionX, instrument.pickup.pickupPossitionY, instrument.pickup.pickupPossitionZ);

    this->setScalarForceLost(instrument.resonance.scalarForceLost);
    this->setConstantForceLost(instrument.resonance.constantForceLost);
}

void SimulatorManager::precallSimulator(Instrument& instrument) {
    this->setInstrument(instrument);
    this->calculatePrecal();
    this->precalcResonanceQuotient(instrument);
    resonanceForce = Eigen::VectorXd::Zero(instrument.precalModel.possitiveW.size());
}

void SimulatorManager::calculateFrame(const Eigen::VectorXd& forcesF, double timeF, double timeV, std::vector<double>& waves) {
    if (SimulatorManager::resonance) this->calculateImpulsForces(forcesF + resonanceForce, timeF);
    else this->calculateImpulsForces(forcesF, timeF);

    unsigned int size = ceil(timeV * SimulatorManager::SampleRate);
    waves = std::vector<double>(size, 0); double t = 0;

    for (unsigned int j = 0; j < size; ++j) {
        t += 1.0 / SimulatorManager::SampleRate;
        Eigen::VectorXd modesOfVibrationZ;
        this->calculateVibrations(t, modesOfVibrationZ);
        waves[j] = 0;

        for (unsigned int i = 0; i < modesOfVibrationZ.size(); i += 3) {
            modesOfVibrationZ[i]     = Instrument::isNumerical(modesOfVibrationZ[i]) ? modesOfVibrationZ[i] : 0;
            modesOfVibrationZ[i + 1] = Instrument::isNumerical(modesOfVibrationZ[i + 1]) ? modesOfVibrationZ[i + 1] : 0;
            modesOfVibrationZ[i + 2] = Instrument::isNumerical(modesOfVibrationZ[i + 2]) ? modesOfVibrationZ[i + 2] : 0;

            if (SimulatorManager::pickup) {
                double x = this->instrument->model3d.vertex(0, i / 3) +
                           modesOfVibrationZ[i];
                double y = this->instrument->model3d.vertex(1, i / 3) +
                           modesOfVibrationZ[i + 1];
                double z = this->instrument->model3d.vertex(2, i / 3) +
                           modesOfVibrationZ[i + 2];
                waves[j] += this->calculatePickup(x, y, z);
            }
            else {
                waves[j] += modesOfVibrationZ[i] +
                            modesOfVibrationZ[i + 1] +
                            modesOfVibrationZ[i + 2];
            }
        }
    }
    resonanceForce = calculateResonanceForce(*instrument, forcesF);
}
