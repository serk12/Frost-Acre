#ifndef INSTRUMENT_HH
#define INSTRUMENT_HH

#include <string>
#include <cmath>

// #include "../../UtilsDebug.h"
#include "String.h"


class Instrument {
public:
    Instrument();
    Instrument(Eigen::Matrix3Xd ver, MatrixXB ed, float e, float t,
               float y, float d, float f, float v);

    double euler;

    Model3D model3D;

    float elasticityK;
    float thicknessT;
    float youngsModulusY;
    float densityD;

    float fluidDampingV;
    float viscoelasticDampingN;

    std::string name; // optional
};

#endif // ifndef INSTRUMENT_HH
