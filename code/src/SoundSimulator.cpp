#include "../header/SoundSimulator.h"

SoundSimulator::SoundSimulator() {
    massM   = Eigen::MatrixXf(0, 0);
    springK = Eigen::MatrixXf(0, 0);

    modesOfVibrationZ        = Eigen::VectorXf(0);
    dampingCoefficientModeWR = Eigen::MatrixXf(0, 0);
    angularFrequencyModeWI   = Eigen::MatrixXf(0, 0);
    gainOfModeC              = Eigen::VectorXf(0);
}

SoundSimulator::SoundSimulator(Instrument instrument,
                               bool calculateNow) : SoundSimulator() {
    this->setInstrument(instrument);

    if (calculateNow) {
        this->calculateMassSpringSystem();
        this->calcuateDoformationModeling();
    }
}

void SoundSimulator::setInstrument(Instrument instrument) {
    this->instrument = instrument;
}

void SoundSimulator::calculateMassSpringSystem() {}

void SoundSimulator::calcuateDoformationModeling() {}

bool SoundSimulator::isCalculatedMassSistem() {
    return massM.size() == 0 and
           springK.size() == 0;
}
bool SoundSimulator::isCalculatedDeformationModeling() {
    return modesOfVibrationZ.size() == 0 and
           dampingCoefficientModeWR.size() == 0 and
           angularFrequencyModeWI.size() == 0 and
           gainOfModeC.size() == 0;
}
