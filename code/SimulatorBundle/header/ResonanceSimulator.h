#ifndef RESONANCESIMULATOR_HH
#define RESONANCESIMULATOR_HH

#include "EigenUtils.h"
#include "Instrument.h"

class ResonanceSimulator {
public:
    void precalcResonanceQuotient(Instrument& instrument);
    Eigen::VectorXd calculateResonanceForce(const Instrument& instrument, const Eigen::VectorXd& force);
    void setScalarForceLost(double scalar);
    void setConstantForceLost(double constant);
private:
    double scalarForceLost;
    double constanForceLost;
};

#endif // ifndef RESONANCESIMULATOR_HH
