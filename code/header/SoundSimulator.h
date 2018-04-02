#ifndef SOUNDSIMULATOR_HH
#define SOUNDSIMULATOR_HH

#include <Eigen/Dense>
#include <iostream>

#include "Instrument"

class SoundSimulator {
public:
  void calculateMassSpringSystem();
  

private:
  Instrument instrument;

  bool massesSpringsAreCalculated;

  Eigen::MatrixXd mass;
  Eigen::MatrixXd spring;



};

#endif
