#include "../header/PickupSimulator.h"

const int PickupSimulator::n = 10;

double PickupSimulator::magneticFieldModul(double phi, double rho) {
    double x = xWire - (xPickup - rho * cos(phi));
    double y = yWire - (yPickup - rho * sin(phi));
    double z = zWire - zPickup;
    return (magneticChargeDensity * rho) / (x * x + y * y + z * z);
}

double PickupSimulator::calculatePickup(double xWire, double yWire, double zWire) {
    this->xWire = xWire; this->yWire = yWire; this->zWire = zWire;
    double result = 0;
    #pragma omp parallel shared(result)
    {
        double phi = 0;
        #pragma omp for
        for (int i = 0; i < PickupSimulator::n; ++i) {
            double rho = 0;
            for (int j = 0; j < PickupSimulator::n; ++j) {
                double field = magneticFieldModul(phi, rho);

                if ((i != 0) || (i != PickupSimulator::n - 1)) field *= 2;
                if ((j != 0) || (j != PickupSimulator::n - 1)) field *= 2;
                result += field;
                rho    +=  radiusPickup / PickupSimulator::n;
            }
            phi += 2 * M_PI / PickupSimulator::n;
        }
    }

    double xp = ((-xWire + xPickup) / 2) - zWire;
    double yp = ((-yWire + yPickup) / 2) - zWire;
    double zp = ((-zWire + zPickup) / 2) - zWire;

    double aux = xp * xp + yp * yp + zp * zp;
    result *= ((2 * M_PI / PickupSimulator::n) *
               (radiusPickup / PickupSimulator::n) / 4) *
              ((zWire - zp) / (std::sqrt(aux * aux * aux)));
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
