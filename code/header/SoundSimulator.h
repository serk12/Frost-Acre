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

private:
  Instrument instrument;

  bool massSpringIsCalculated;
  Eigen::MatrixXf mass;
  Eigen::MatrixXf spring;

  bool deformationModelingIsCalculated;
  Eigen::VectorXf modesOfVibrationZ;
  Eigen::MatrixXf dampingCoefficientModeWR;
  Eigen::MatrixXf angularFrequencyModeWI;
  Eigen::VectorXf gainOfModeC;
};

#endif
