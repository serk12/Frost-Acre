#ifndef INSTRUMENT_HH
#define INSTRUMENT_HH

#include <string>
#include <cmath>
#include <vector>

#include "../../EigenUtils.h"


struct Material {
    double elasticityK;
    double thicknessT;
    double youngsModulusY;
    double densityD;
    double fluidDampingV;
    double viscoelasticDampingN;
};

class Instrument {
public:
    Instrument();
    Instrument(Model3D& model3d);
    Instrument(std::vector<Material>& material, Model3D& model3d);

    void setModel3D(Model3D& model3d);
    void getModel3D(Model3D& model3d);

    void setPrecalModel(PrecalModel& precalModel);
    void getPrecalModel(PrecalModel& precalModel);

    double euler;

    Model3D model3d;
    PrecalModel precalModel;
    std::vector<Material> material;
private:
};

#include "../../DebugUtils.h"

#endif // ifndef INSTRUMENT_HH
