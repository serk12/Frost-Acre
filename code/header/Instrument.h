#ifndef INSTRUMENT_HH
#define INSTRUMENT_HH

#include <Eigen/Dense>
#include <iostream>

class Instrument {

public:
  Eigen::MatrixXd vertex;
  Eigen::MatrixXd edge;

  float elasticityK;
  float thicknessT;
  float youngsModulus;
  float density;

};

#endif
