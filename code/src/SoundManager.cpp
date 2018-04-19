#include "../header/SoundManager.h"

SoundManager::SoundManager() {
    massM   = Eigen::MatrixXf(0, 0);
    springK = Eigen::MatrixXf(0, 0);

    modesOfVibrationZ        = Eigen::VectorXf(0);
    dampingCoefficientModeWR = Eigen::MatrixXf(0, 0);
    angularFrequencyModeWI   = Eigen::MatrixXf(0, 0);
    gainOfModeC              = Eigen::VectorXf(0);
}

SoundManager::SoundManager(Instrument instrument, bool calculateNow)
    : SoundManager() {
    this->setInstrument(instrument);

    if (calculateNow) {
        this->calculateMassSpringSystem();
        this->calcuateDoformationModeling();
    }
}

void SoundManager::setInstrument(Instrument instrument) {
    this->instrument = instrument;
}

void SoundManager::calculateMassSpringSystem() {}

void SoundManager::calcuateDoformationModeling() {}

bool SoundManager::isCalculatedMassSistem() {
    return massM.size() == 0 and
           springK.size() == 0;
}
bool SoundManager::isCalculatedDeformationModeling() {
    return modesOfVibrationZ.size() == 0 and
           dampingCoefficientModeWR.size() == 0 and
           angularFrequencyModeWI.size() == 0 and
           gainOfModeC.size() == 0;
}
