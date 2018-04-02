#ifndef SOUNDSIMULATOR_HH
#define SOUNDSIMULATOR_HH

#include <Eigen/Dense>
#include <iostream>

#include "Instrument.h"

class SoundSimulator {
public:

    SoundSimulator();
    SoundSimulator(Instrument instrument, bool calculateNow);

    void setInstrument(Instrument instrument);
    void calculateMassSpringSystem();
    void calcuateDoformationModeling();
    void calculateImpulsForces(Eigen::VectorXf forcesF);

    // si las mastrizes estan vacias o el instrumento es vacio tambien o no
    // hemos calculado nada
    bool isCalculatedMassSistem();
    bool isCalculatedDeformationModeling();
private:

    Instrument instrument;

    Eigen::MatrixXf massM;
    Eigen::MatrixXf springK;

    Eigen::VectorXf modesOfVibrationZ;
    Eigen::MatrixXf dampingCoefficientModeWR;
    Eigen::MatrixXf angularFrequencyModeWI;
    Eigen::VectorXf gainOfModeC;
};

#endif // ifndef SOUNDSIMULATOR_HH
