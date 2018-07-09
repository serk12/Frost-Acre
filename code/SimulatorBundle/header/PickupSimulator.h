#ifndef PICKUPSIMULATOR_HH
#define PICKUPSIMULATOR_HH
#define M_PI 3.14159265358979323846

#include <math.h>

class PickupSimulator {
public:
    static const double n;
    double xWire, yWire, zWire, xPickup, yPickup, zPickup, gamma, radiusPickup;
    double calculate(double xWire, double yWire, double zWire);

    void setGamma(double gamma);
    void setRadiusPickup(double radiusPickup);
    void setPickupPossition(double xPickup, double yPickup, double zPickup);

private:
    double magneticFieldModul(double phi, double rho);
};

#endif // ifndef PICKUPSIMULATOR_HH
