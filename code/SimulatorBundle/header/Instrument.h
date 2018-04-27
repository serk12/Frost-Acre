#ifndef INSTRUMENT_HH
#define INSTRUMENT_HH

#include <string>
#include <cmath>

// #include "../../DebugUtils.h"
#include "../../EigenUtils.h"


class Instrument {
public:
    Instrument();
    Instrument(Model3D& model3d);
    Instrument(double k, double t, double y, double d,
               double v, double n, Model3D& model3d);

    void setModel3D(Model3D& model3d);
    void getModel3D(Model3D& model3d);

    void setPrecalModel(PrecalModel& precalModel);
    void getPrecalModel(PrecalModel& precalModel);

    double elasticityK;
    double thicknessT;
    double youngsModulusY;
    double densityD;
    double fluidDampingV;
    double viscoelasticDampingN;

    double euler;

    Model3D model3d;
    PrecalModel precalModel;
private:
};

#endif // ifndef INSTRUMENT_HH
