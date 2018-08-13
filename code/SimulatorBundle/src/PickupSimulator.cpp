#include "../header/PickupSimulator.h"

const double PickupSimulator::n = 20;

double PickupSimulator::magneticFieldModul(double phi, double rho) {
    double x = xWire - (xPickup - rho * std::cos(phi));
    double y = yWire - (yPickup - rho * std::sin(phi));
    double z = zWire - zPickup;
    return (magneticChargeDensity * rho) / (x * x + y * y + z * z);
}

double PickupSimulator::calculatePickup(double xWire, double yWire, double zWire) {
    this->xWire = xWire; this->yWire = yWire; this->zWire = zWire;
    double result = 0;
    for (double phi = 0, i = 0; i < PickupSimulator::n; phi += 2 * M_PI / PickupSimulator::n, ++i) {
        for (double rho = 0, j = 0; j < PickupSimulator::n; rho +=  radiusPickup / PickupSimulator::n, ++j) {
            double field = magneticFieldModul(phi, rho);
            if ((j != 0) || (j != PickupSimulator::n - 1)) field *= 2;
            if ((i != 0) || (i != PickupSimulator::n - 1)) field *= 2;
            field  *= ((2 * M_PI / PickupSimulator::n) * (radiusPickup / PickupSimulator::n)) / 4;
            result += field;
        }
    }
    return result;
}

void PickupSimulator::setMagneticChargeDensity(double magneticChargeDensity) {
    this->magneticChargeDensity = magneticChargeDensity;
}

void PickupSimulator::setRadiusPickup(double radiusPickup) {
    this->radiusPickup = radiusPickup;
}

void PickupSimulator::setPickupPossition(double xPickup, double yPickup, double zPickup) {
    this->xPickup = xPickup;
    this->yPickup = yPickup;
    this->zPickup = zPickup;
}
