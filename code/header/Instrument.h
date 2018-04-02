#ifndef INSTRUMENT_HH
#define INSTRUMENT_HH

#include <Eigen/Dense>
#include <iostream>
#include <cmath>

class Instrument {

public:
  Instrument();
  double euler;

  Eigen::MatrixXd vertex;
  Eigen::MatrixXd edge;

  float elasticityK;
  float thicknessT;
  float youngsModulus;
  float density;

  float fluidDamping;
  float viscoelasticDamping;

};

#endif
