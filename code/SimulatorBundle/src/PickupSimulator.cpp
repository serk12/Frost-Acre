#include "../header/PickupSimulator.h"

const double PickupSimulator::n = 10;

double PickupSimulator::magneticFieldModul(double phi, double rho) {
    double x = xWire - (xPickup - rho * std::cos(phi));
    double y = yWire - (yPickup - rho * std::sin(phi));
    double z = zWire - zPickup;
    return (magneticChargeDensity * rho) / (x * x + y * y + z * z);
}

double PickupSimulator::calculatePickup(double xWire, double yWire, double zWire) {
    this->xWire = xWire; this->yWire = yWire; this->zWire = zWire;
    double result = 0;
    for (double phi = 0; phi <= 2 * M_PI; phi += 2 * M_PI / PickupSimulator::n) {
        for (double rho = 0; rho <= radiusPickup; rho +=  radiusPickup / PickupSimulator::n) {
            double field = magneticFieldModul(phi, rho);
            if ((phi != 0) || ((phi +      2 * M_PI / PickupSimulator::n) >     2 * M_PI)) field *= 2;
            if ((rho != 0) || ((rho +  radiusPickup / PickupSimulator::n) > radiusPickup)) field *= 2;
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
