#ifndef PICKUPSIMULATOR_HH
#define PICKUPSIMULATOR_HH
#define M_PI 3.14159265358979323846

#include "../../Controller/header/DebugController.h"
#include <math.h>

class PickupSimulator {
public:
    static const int n;
    double xWire, yWire, zWire, xPickup, yPickup, zPickup, magneticChargeDensity, radiusPickup;

    void setMagneticChargeDensity(double magneticChargeDensity);
    void setRadiusPickup(double radiusPickup);
    void setPickupPossition(double xPickup, double yPickup, double zPickup);

protected:
    double calculatePickup(double xWire, double yWire, double zWire);

private:
    inline double magneticFieldModul(double phi, double rho);
};

#endif // ifndef PICKUPSIMULATOR_HH
