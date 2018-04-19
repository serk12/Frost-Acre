#ifndef INSTRUMENT_HH
#define INSTRUMENT_HH

#include <Eigen/Dense>
#include <iostream>
#include <cmath>

class Instrument {
public:
    Instrument();
    Instrument(Eigen::MatrixXd ver, Eigen::MatrixXd ed, float e, float t,
               float y, float d, float f, float v);

    double euler;

    Eigen::MatrixXd vertex;
    Eigen::MatrixXd edge;

    float elasticityK;
    float thicknessT;
    float youngsModulusY;
    float densityD;

    float fluidDampingV;
    float viscoelasticDampingN;
};

#endif // ifndef INSTRUMENT_HH
