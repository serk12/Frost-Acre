#ifndef INSTRUMENT_HH
#define INSTRUMENT_HH

#include <string>
#include <math.h>
#include <vector>

#include "EigenUtils.h"


struct Material {
    double thicknessT;
    double youngsModulusY;
    double densityD;
    double fluidDampingV;
    double viscoelasticDampingN;
    Material() {}
    Material(int k) :
        thicknessT(k),
        youngsModulusY(k),
        densityD(k),
        fluidDampingV(k),
        viscoelasticDampingN(k) {}
};

struct Pickup {
    double magneticChargeDensity;
    double radiusPickup;
    double pickupPossitionX;
    double pickupPossitionY;
    double pickupPossitionZ;
};

struct Resonance {
    double scalarForceLost;
    double constantForceLost;
};

class Instrument {
public:
    Instrument();
    Instrument(Model3D& model3d);
    Instrument(std::vector<Material>& material, Model3D& model3d);
    Instrument(Instrument& model3d);

    void setModel3D(Model3D& model3d);
    void getModel3D(Model3D& model3d);

    void setPrecalModel(PrecalModel& precalModel);
    void getPrecalModel(PrecalModel& precalModel);

    static bool isNumerical(double num);

    double euler;

    Model3D model3d;
    PrecalModel precalModel;
    std::vector<Material> material;

    Eigen::VectorXd resonanceRatio;
private:
};

#include "../../Controller/header/DebugController.h"

#endif // ifndef INSTRUMENT_HH
